#include "MainMenu.hpp"

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
    if (_velo != nullptr) {
			auto pos = getPosition();
			if (pos.y + (_texture->getSize().y) * 2.5 <= 0) {
				_velo->destroy();
				_velo = nullptr;
			}
		}
  }
  void Layers::setVelocity(const sf::Vector2f &pos) noexcept
	{
		if (_velo == nullptr)
			_velo = &addComponent<sfs::Velocity>(pos);
		else {
			_velo->destroy();
			_velo = &addComponent<sfs::Velocity>(pos);			
		}
	}

  void Scroller::start(sfs::Scene &scene) noexcept
  {
    _scroller = &addChild<Layers>(scene, "assets/sprites/Nuages.jpg",
				    sf::Vector2f(1.2, 1.2),
				    sf::Vector2f(-150, 0));
	_scroller->addChild<Layers>(scene, "assets/sprites/trainBackground.png",
				    sf::Vector2f(1, 1), sf::Vector2f(-300, 0),
				    sf::Vector2f(0, 930));
	_scroller->addChild<Layers>(scene, "assets/sprites/test.png",
				    sf::Vector2f(1, 2.5), sf::Vector2f(-250, 0),
				    sf::Vector2f(0, 190));
	_scroller->addChild<Layers>(scene, "assets/sprites/rangéImeubles.png",
				    sf::Vector2f(1, 1), sf::Vector2f(-325, 0),
				    sf::Vector2f(0, 600));
   	_scroller->addChild<Layers>(scene, "assets/sprites/Mimeubles.png",
				    sf::Vector2f(1, 2.5), sf::Vector2f(-350, 0),
				    sf::Vector2f(0, 515));
	  //_scroller->addChild<Layers>(scene, "assets/sprites/imeubles.png",
	  //sf::Vector2f(1, 2.5), sf::Vector2f(-350, 0), sf::Vector2f(0, 800));
	_scroller->addChild<Layers>(scene, "assets/sprites/traks.png",
				    sf::Vector2f(1, 1), sf::Vector2f(-500, 0),
				    sf::Vector2f(0, 1040));
	_scroller->addChild<Layers>(scene, "assets/sprites/train.png",
				    sf::Vector2f(0.5, 0.5),
				    sf::Vector2f(550, 0), sf::Vector2f(0, 979));
	_scroller->addChild<Layers>(scene, "assets/sprites/FirstLayer.png",
				    sf::Vector2f(1, 2), sf::Vector2f(-550, 0),
				    sf::Vector2f(0, 930));
  }

  void Scroller::restoreInitialSpeed(sfs::Scene &scene) noexcept
  {
	  auto layers = scene.getGameObjects<Layers>();
	  for (auto &i : layers) {
		  i->setVelocity(i->getSpeed());
	  }
  }
}
