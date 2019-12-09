#include <math.h>

#include "GoPlayer.hpp"

namespace cf {
GoPlayer::GoPlayer(uint64_t id, const std::string &name, const struct stats &stats,
		   const sf::Color &color, const std::string &sprite,
		   UdpPrctl::weaponType weaponType) noexcept
	: UdpGameObject(id)
	, _stats(stats)
	, _color(color)
	, _spriteName(sprite)
	, _playerSprite(nullptr)
	, _playerName(nullptr)
	, _velocity(addComponent<sfs::Velocity>())
{
	UdpGameObject::name(name);
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
	auto pRect = _playerSprite->getGlobalBounds();
	auto tRect = _playerName->getGlobalBounds();
	_playerSprite->setOrigin(pRect.width / 2, pRect.height / 2);
	_playerName->setOffset(sf::Vector2f((pRect.width - tRect.width) / 2 - pRect.width / 2,
					    -tRect.height - 5 - pRect.height / 2));
	scene.subscribe(*this, sf::Event::MouseMoved);
}

void GoPlayer::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
{
	sf::Vector2f delta(getPosition());

	delta.x -= event.mouseMove.x;
	delta.y -= event.mouseMove.y;
	float angle = atan2(delta.y, delta.x);
	_playerSprite->setRotation(angle * 180 / M_PI + 145);
}

sfs::Sound &GoPlayer::getAttackSound() noexcept
{
	return *_sound;
}
} // namespace cf