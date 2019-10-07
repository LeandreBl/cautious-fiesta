#pragma once

#include <GameObject.hpp>
#include <BasicShape.hpp>
#include <Velocity.hpp>

namespace cf {
    class optionBackground : public sfs::GameObject
    {
        public:
            optionBackground() noexcept
                : _image(nullptr), _velo(nullptr) {};
            void start(sfs::Scene &scene) noexcept 
            {
                srand(time(nullptr));
                setPosition(sf::Vector2f(0, 1400));
                int choice = std::rand() % 2;
                if (choice == 0)
                    _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/OptionBackground.png"));
                else if (choice == 1)
                    _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/Metro.png"));
                _velo = &addComponent<sfs::Velocity>(sf::Vector2f(0, -550));
            }
            void update(sfs::Scene &) noexcept
            {
                if (_velo != nullptr) {
                    auto pos = getPosition();
                    if (pos.y <= 0) {
                        pos.y = 0;
                        _velo->destroy();
                        _velo = nullptr;
                    }
                }
            }
        protected:
            sfs::Sprite *_image;
            sfs::Velocity *_velo;
    };
}
