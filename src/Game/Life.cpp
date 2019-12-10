#include <Offset.hpp>
#include "Life.hpp"
#include "GameManager.hpp"
#include "SpriteSheetLoader.hpp"

namespace cf {
Life::Life(uint64_t id) noexcept
	: sfs::UI(sf::Vector2f(), "GameUi : Life")
	, _maxLife(0)
	, _heart(nullptr)
	, _lifeDisplay(nullptr)
	, _id(id)
{
}

void Life::start(sfs::Scene &scene) noexcept
{
	auto gameManager = scene.getGameObjects<GameManager>();
	if (!gameManager.empty()) {
		SpriteSheetLoader loader("assets/SpriteSheets/HeartSpriteSheet.txt");

		_maxLife = gameManager[0]->_character.getLife();
		_heart = &addComponent<sfs::Sprite>(*scene.getAssetTexture(loader.getSpritePath()),
						    sf::Vector2f(-500, -500));
		_lifeDisplay = &addComponent<sfs::Text>(
			*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"),
			std::to_string((int)_maxLife), sf::Color::Black, 35,
			sf::Vector2f(-550, -550));
		_frames = loader.getFrames();
		_heart->setTextureRect(_frames[0]);
		_heart->setScale(sf::Vector2f(10, 10));

		auto pos = (1920 / 2) - _heart->getGlobalBounds().width / 2;
		_heart->setOffset(sf::Vector2f(pos, 980));
		pos = (1920 / 2) - _lifeDisplay->getGlobalBounds().width / 2;
		_lifeDisplay->setOffset(sf::Vector2f(pos, 1000));
	}
}

void Life::changeLife(float life, uint64_t id) noexcept
{
	if (_id == id + 1000) {
		_lifeDisplay->setString(std::to_string((int)life));
		auto percentage = (life * 100) / _maxLife;
		int frame = 0;
		if (percentage < 80)
			frame = 1;
		if (percentage < 60)
			frame = 2;
		if (percentage < 40) {
			frame = 3;
			_lifeDisplay->setFillColor(sf::Color::White);
		}
		if (percentage < 20)
			frame = 4;
		if (percentage < 10)
			frame = 5;
		if (percentage < 3)
			destroy();
		_heart->setTextureRect(_frames[frame]);
	}
}
} // namespace cf