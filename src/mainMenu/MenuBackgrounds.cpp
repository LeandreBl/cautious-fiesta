#include "MenuBackgrounds.hpp"

namespace cf
{
  void Layers::start(sfs::Scene &scene) noexcept
  {
    _texture = scene.getAssetTexture(_path);
    if (_texture == nullptr)
      scene.close();
    addComponent<DrawLayers>(*_texture, _origin).setScale(_scale);
	setVelocity(_speed);
  }

  void Layers::update(sfs::Scene &) noexcept 
  {
    if (_velo != nullptr && lock == false) {
			auto pos = getPosition();
			if (pos.y <= ((-1300) + _origin.y)) {
				_velo->destroy();
				_velo = nullptr;
				lock = true;
			}
		}
	if (_velo != nullptr && lock == true) {
			auto pos = getPosition();
			if (pos.y >= _origin.y) {
				_velo->destroy();
				_velo = nullptr;
				lock = false;
			}
  	}
  }

  void Layers::setVelocity(const sf::Vector2f &pos) noexcept
	{
		if (_velo == nullptr)
			_velo = &addComponent<sfs::Velocity>(pos);
		else {
			_velo->destroy();
			_velo = nullptr;
			_velo = &addComponent<sfs::Velocity>(pos);			
		}
	}

  void Scroller::start(sfs::Scene &scene) noexcept
  {
    _scroller = &addChild<Layers>(scene, "assets/sprites/Menu/scroller/sky.jpg",
				    sf::Vector2f(1.2, 1.5),
				    sf::Vector2f(-150, 0));
	_scroller->addChild<Layers>(scene, "assets/sprites/Menu/scroller/Building1.png",
					sf::Vector2f(1, 1), sf::Vector2f(-300, 0),
					sf::Vector2f(0, 360));
	_scroller->addChild<Layers>(scene, "assets/sprites/Menu/scroller/trainBackground.png",
				    sf::Vector2f(1, 1), sf::Vector2f(-350, 0),
				    sf::Vector2f(0, 930));
	_scroller->addChild<Layers>(scene, "assets/sprites/Menu/scroller/Building2.png",
				    sf::Vector2f(1, 2.5), sf::Vector2f(-400, 0),
				    sf::Vector2f(0, 190));
	_scroller->addChild<Layers>(scene, "assets/sprites/Menu/scroller/MBuildings1.png",
				    sf::Vector2f(1, 1.2), sf::Vector2f(-450, 0),
				    sf::Vector2f(0, 600));
	_scroller->addChild<Layers>(scene, "assets/sprites/Menu/scroller/MBuildings3.png",
				    sf::Vector2f(1, 1), sf::Vector2f(-500, 0),
				    sf::Vector2f(0, 600));
   	_scroller->addChild<Layers>(scene, "assets/sprites/Menu/scroller/MBuildings2.png",
				    sf::Vector2f(1, 2.5), sf::Vector2f(-550, 0),
				    sf::Vector2f(0, 515));
	_scroller->addChild<Layers>(scene, "assets/sprites/Menu/scroller/traks.png",
				    sf::Vector2f(1, 1), sf::Vector2f(-600, 0),
				    sf::Vector2f(0, 1040));
	_scroller->addChild<Layers>(scene, "assets/sprites/Menu/scroller/trainFirstground.png",
				    sf::Vector2f(0.5, 0.5),
				    sf::Vector2f(550, 0), sf::Vector2f(0, 979));
	_scroller->addChild<Layers>(scene, "assets/sprites/Menu/scroller/FirstLayer.png",
				    sf::Vector2f(1, 2), sf::Vector2f(-650, 0),
				    sf::Vector2f(0, 930));
  }

  void Scroller::setLayersSpeed(sfs::Scene &scene, bool initialSpeed, sf::Vector2f speed) noexcept
  {
	auto layers = scene.getGameObjects<Layers>();
	if (initialSpeed == true)
	  	for (auto &i : layers)
			i->setVelocity(i->getSpeed());
	else if (initialSpeed == false)
		for (auto &i : layers)
			i->setVelocity(speed);
  }
}
