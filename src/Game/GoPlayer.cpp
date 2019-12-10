#include <Vector.hpp>

#include "GoPlayer.hpp"
#include "GameManager.hpp"

namespace cf {
GoPlayer::GoPlayer(GameManager &manager, uint64_t id, const std::string &name,
		   const struct stats &stats, const sf::Color &color, const std::string &sprite,
		   UdpPrctl::weaponType weaponType) noexcept
	: UdpGameObject(id)
	, _manager(manager)
	, _stats(stats)
	, _color(color)
	, _spriteName(sprite)
	, _playerSprite(nullptr)
	, _playerName(nullptr)
	, _velocity(addComponent<sfs::Velocity>())
{
	/* TODO */
	(void)weaponType;
	UdpGameObject::name(name);
}

void GoPlayer::onDestroy() noexcept
{
	if (_manager._self == this)
		_manager._self = nullptr;
	for (auto it = _manager._players.begin(); it != _manager._players.end(); ++it) {
		if (*it == this) {
			_manager._players.erase(it);
			break;
		}
	}
	_manager._popup->push("You died", 3);
	_manager._popup->push("Press [Enter] to quit", 10);
}

void GoPlayer::start(sfs::Scene &scene) noexcept
{
	auto *texture = scene.getAssetTexture(_spriteName);

	if (texture == nullptr) {
		std::cerr << _spriteName << " texture not found" << std::endl;
		destroy();
		return;
	}
	_playerSprite = &addComponent<sfs::Sprite>(*texture);
	_playerSprite->setColor(_color);
	auto *font = scene.getAssetFont("");
	if (font == nullptr) {
		std::cerr << "no font found" << std::endl;
		destroy();
		return;
	}
	_playerName = &addComponent<sfs::Text>(*font, name(), sf::Color::White, 20);
	auto *sound = scene.getAssetSoundBuffer("local-assets/musics/laser.ogg");
	if (sound == nullptr) {
		std::cerr << "laser sound not found" << std::endl;
		destroy();
		return;
	}
	_sound = &addComponent<sfs::Sound>(*sound);
	_sound->setVolume(20);
	auto pRect = _playerSprite->getGlobalBounds();
	auto tRect = _playerName->getGlobalBounds();
	_playerSprite->setOrigin(pRect.width / 2, pRect.height / 2);
	_playerName->setOffset(sf::Vector2f((pRect.width - tRect.width) / 2 - pRect.width / 2,
					    -tRect.height - 5 - pRect.height / 2));
	scene.subscribe(*this, sf::Event::MouseMoved);
	scene.subscribe(*this, sf::Event::MouseButtonPressed);
}

void GoPlayer::update(sfs::Scene &) noexcept
{
	float angle = sfs::angle(getPosition(), _lastMousePos);
	_playerSprite->setRotation(angle * 180 / M_PI - 45);
}

void GoPlayer::onEvent(sfs::Scene &, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::MouseButtonPressed)
		_lastMousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
	else if (event.type == sf::Event::MouseMoved)
		_lastMousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
}

sfs::Sound &GoPlayer::getAttackSound() noexcept
{
	return *_sound;
}
} // namespace cf