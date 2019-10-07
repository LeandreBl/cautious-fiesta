#pragma once

#include <GameObject.hpp>
#include <BasicShape.hpp>
#include <Velocity.hpp>
#include "MainMenu.hpp"

namespace cf {
    class optionBackground : public sfs::GameObject
    {
        public:
            optionBackground() noexcept
                : _image(nullptr), _velo(nullptr) {};
            void start(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &) noexcept;
            sf::FloatRect getGlobalBounds() noexcept;
        protected:
            sfs::Sprite *_image;
            sfs::Velocity *_velo;
    };

    class optionSound : public sfs::UI
    {

    };

    class optionScene : public sfs::UI
    {
        public:
            optionScene() noexcept : _soundText(nullptr), _decreaseSound(nullptr), _augmentSound(nullptr) {};
            void start(sfs::Scene &scene) noexcept {
                _soundText = &addComponent<sfs::Text>(*scene.getAssetFont("assets/fonts/commodore-64.ttf"), "SOUND", sf::Color::White, 30);
                _decreaseSound = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"), 
                                                        sf::Vector2f(-100, 0), std::bind(&optionScene::lowerSound, this, std::ref(scene)));
               _decreaseSound->setScale(sf::Vector2f(1.5, 1.5));
               _decreaseSound->addComponent<PadderH<sfs::Button>>(0, *_decreaseSound);
               _decreaseSound->addComponent<PadderW<sfs::Button>>(-100, *_decreaseSound);

                _augmentSound = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"), 
                                                        sf::Vector2f(-100, 0), std::bind(&optionScene::augmentSound, this, std::ref(scene)));
                _augmentSound->setScale(sf::Vector2f(1.5, 1.5));
                _augmentSound->setRotate(180);
                _augmentSound->addComponent<PadderH<sfs::Button>>(0, *_augmentSound);
                _augmentSound->addComponent<PadderW<sfs::Button>>(100, *_augmentSound);
            }
            void lowerSound(sfs::Scene &scene) noexcept;
            void augmentSound(sfs::Scene &scnene) noexcept;
            sf::FloatRect getGlobalBounds() noexcept {return _soundText->getGlobalBounds();}
        protected:
            sfs::Text *_soundText;
            sfs::Button *_decreaseSound;
            sfs::Button *_augmentSound;
    };
}
