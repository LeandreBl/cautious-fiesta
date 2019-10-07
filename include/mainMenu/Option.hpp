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
        public:
            optionSound() noexcept : _soundText(nullptr), _decreaseSound(nullptr), _augmentSound(nullptr) {};
            void start(sfs::Scene &scene) noexcept {
                _soundText = &addComponent<sfs::Text>(*scene.getAssetFont("assets/fonts/commodore-64.ttf"), "SOUND", sf::Color::White, 30);
                _decreaseSound = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"), 
                                                        sf::Vector2f(-100, 0), std::bind(&optionSound::lowerSound, this, std::ref(scene)));
               _decreaseSound->setScale(sf::Vector2f(1.5, 1.5));
               _decreaseSound->addComponent<PadderH<sfs::Button>>(0, *_decreaseSound);
               _decreaseSound->addComponent<PadderW<sfs::Button>>(-100, *_decreaseSound);

                _augmentSound = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"), 
                                                        sf::Vector2f(-100, 0), std::bind(&optionSound::augmentSound, this, std::ref(scene)));
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

    class optionFrameRate : public sfs::UI
    {
        public:
            optionFrameRate() noexcept : _frameRateText(nullptr), _decreaseFrameRate(nullptr), _augmentFrameRate(nullptr) {};
            void start(sfs::Scene &scene) noexcept {
                _frameRateText = &addComponent<sfs::Text>(*scene.getAssetFont("assets/fonts/commodore-64.ttf"), "FRAME RATE", sf::Color::White, 30);
                _decreaseFrameRate = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"), 
                                                        sf::Vector2f(-100, 0), std::bind(&optionFrameRate::lowerFrame, this, std::ref(scene)));
               _decreaseFrameRate->setScale(sf::Vector2f(1.5, 1.5));
               _decreaseFrameRate->addComponent<PadderH<sfs::Button>>(100, *_decreaseFrameRate);
               _decreaseFrameRate->addComponent<PadderW<sfs::Button>>(-100, *_decreaseFrameRate);

                _augmentFrameRate = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"), 
                                                        sf::Vector2f(-100, 0), std::bind(&optionFrameRate::augmentFrame, this, std::ref(scene)));
                _augmentFrameRate->setScale(sf::Vector2f(1.5, 1.5));
                _augmentFrameRate->setRotate(180);
                _augmentFrameRate->addComponent<PadderH<sfs::Button>>(100, *_augmentFrameRate);
                _augmentFrameRate->addComponent<PadderW<sfs::Button>>(100, *_augmentFrameRate);
            }
            void lowerFrame(sfs::Scene &scene) noexcept
            {
                auto frame = scene.framerate();
                if (frame - 20 <= 0)
                    frame = 0;
                else
                    frame -= 20;
                scene.framerate(frame);
            }
            void augmentFrame(sfs::Scene &scene) noexcept
            {
                auto frame = scene.framerate();
                if (frame + 20 >= 200)
                    frame = 200;
                else
                    frame += 20;
                scene.framerate(frame);
            }
            sf::FloatRect getGlobalBounds() noexcept {return _frameRateText->getGlobalBounds();}
        protected:
            sfs::Text *_frameRateText;
            sfs::Button *_decreaseFrameRate;
            sfs::Button *_augmentFrameRate;
    };

    class optionScene : public sfs::UI
    {
        public:
            optionScene() noexcept : _sound(nullptr), _frameRate(nullptr) {};
            void start(sfs::Scene &scene) noexcept {
                _sound = &addChild<optionSound>(scene); //TODO bien place les buttons
                _sound->addComponent<PadderW<optionSound>>(0, *_sound);
				_sound->addComponent<PadderH<optionSound>>(0, *_sound);
                _frameRate = &addChild<optionFrameRate>(scene); //TODO bien place les buttons
                _frameRate->addComponent<PadderW<optionFrameRate>>(0, *_frameRate);
                _frameRate->addComponent<PadderH<optionFrameRate>>(100, *_frameRate);
                //TODO placer la box de background pour que ce soit generic a tout le jeu
            }
        protected:
            optionSound *_sound;
            optionFrameRate *_frameRate;
    };
}
