#include "MainMenu.hpp"

namespace cf
{
  void Layers::start(sfs::Scene &scene) noexcept
  {
    _texture = scene.getAssetTexture(_path);
    if (_texture == nullptr)
      scene.close();
    addComponent<DrawLayers>(*_texture).setScale(1.2, 1);
    addComponent<sfs::Velocity>(sf::Vector2f(-192, 0));
  }
}
