#include "MainMenu.hpp"

namespace cf
{
  void Layers::start(sfs::Scene &scene) noexcept
  {
    _texture = scene.getAssetTexture(_path);
    if (_texture == nullptr)
      scene.close();
    addComponent<DrawLayers>(*_texture, _origin).setScale(_scale);
    addComponent<sfs::Velocity>(sf::Vector2f(_speed));
  }
}
