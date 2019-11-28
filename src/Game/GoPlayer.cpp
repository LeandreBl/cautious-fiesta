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
	// weapon todo
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
		std::cerr << "not font found" << std::endl;
		destroy();
		return;
	}
	_playerName = &addComponent<sfs::Text>(*font, name(), sf::Color::White, 20);
	auto pRect = _playerSprite->getLocalBounds();
	auto tRect = _playerName->getLocalBounds();
	_playerName->setOffset(sf::Vector2f((pRect.width - tRect.width) / 2, -tRect.height - 5));
}

void GoPlayer::update(sfs::Scene &scene) noexcept
{
}
} // namespace cf