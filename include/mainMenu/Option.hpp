#pragma once

#include <GameObject.hpp>
#include <BasicShape.hpp>
#include <Velocity.hpp>
#include "MainMenu.hpp"

namespace cf {
    class Background : public sfs::GameObject
    {
        public:
            Background(const std::string &path = "") noexcept
                : _image(nullptr), _velo(nullptr), _path(path)
                {};
            void start(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &) noexcept;
            sf::FloatRect getGlobalBounds() noexcept;
            void addVelocity(sf::Vector2f speed) noexcept
            {
                if (_velo != nullptr) {
                    _velo->destroy();
                    _velo = nullptr;
                    _velo = &addComponent<sfs::Velocity>(speed);
                } else if (_velo == nullptr) {
                    _velo = &addComponent<sfs::Velocity>(speed);
                }
            }
        protected:
            sfs::Sprite *_image;
            sfs::Velocity *_velo;
            std::string _path;
            bool _lock = false;
    };

    class optionSound : public sfs::UI
    {
        public:
            optionSound() noexcept : _soundText(nullptr), _decreaseSound(nullptr), _augmentSound(nullptr), _soundBar(nullptr) {};
            void start(sfs::Scene &scene) noexcept {
                _soundText = &addComponent<sfs::Text>(*scene.getAssetFont("assets/fonts/commodore-64.ttf"), "SOUND", sf::Color::White, 30);
                _decreaseSound = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"),
                                                        sf::Vector2f(-100, -100), std::bind(&optionSound::lowerSound, this, std::ref(scene)));
                _decreaseSound->setScale(sf::Vector2f(1.5, 1.5));
                _decreaseSound->addComponent<PadderH<sfs::Button>>(-96, *_decreaseSound);
                _decreaseSound->addComponent<PadderW<sfs::Button>>(-86, *_decreaseSound);

                _augmentSound = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"),
                                                        sf::Vector2f(-1000, -1000), std::bind(&optionSound::augmentSound, this, std::ref(scene)));
                _augmentSound->setScale(sf::Vector2f(1.5, 1.5));
                _augmentSound->setRotate(180);
                _augmentSound->addComponent<PadderH<sfs::Button>>(-69, *_augmentSound);
                _augmentSound->addComponent<PadderW<sfs::Button>>(115, *_augmentSound);

                _soundBar = &addComponent<sfs::Rectangle>(sf::Vector2f(-16, 50), sf::Vector2f(150, 30), sf::Color::White);
            }
            void lowerSound(sfs::Scene &scene) noexcept;
            void augmentSound(sfs::Scene &scnene) noexcept;
            sf::FloatRect getGlobalBounds() noexcept {return _soundText->getGlobalBounds();}
        protected:
            sfs::Text *_soundText;
            sfs::Button *_decreaseSound;
            sfs::Button *_augmentSound;
            sfs::Rectangle *_soundBar;
    };

    class optionFrameRate : public sfs::UI
    {
        public:
            optionFrameRate() noexcept : _frameRateText(nullptr), _decreaseFrameRate(nullptr), _augmentFrameRate(nullptr) {};
            void start(sfs::Scene &scene) noexcept {
                _frameRateText = &addComponent<sfs::Text>(*scene.getAssetFont("assets/fonts/commodore-64.ttf"), "FRAME RATE", sf::Color::White, 30);
                _decreaseFrameRate = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"),
                                                        sf::Vector2f(-1000, -1000), std::bind(&optionFrameRate::lowerFrame, this, std::ref(scene)));
               _decreaseFrameRate->setScale(sf::Vector2f(1.5, 1.5));
               _decreaseFrameRate->addComponent<PadderH<sfs::Button>>(100, *_decreaseFrameRate);
               _decreaseFrameRate->addComponent<PadderW<sfs::Button>>(-86, *_decreaseFrameRate);

                _augmentFrameRate = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/ButtonArrow.png"), *scene.getAssetFont("assets/fonts/commodore-64.ttf"),
                                                        sf::Vector2f(-1000, -1000), std::bind(&optionFrameRate::augmentFrame, this, std::ref(scene)));
                _augmentFrameRate->setScale(sf::Vector2f(1.5, 1.5));
                _augmentFrameRate->setRotate(180);
                _augmentFrameRate->addComponent<PadderH<sfs::Button>>(100, *_augmentFrameRate);
                _augmentFrameRate->addComponent<PadderW<sfs::Button>>(115, *_augmentFrameRate);

                framerate = scene.framerate();
                _frameNumber= &addComponent<sfs::Text>(*scene.getAssetFont("assets/fonts/commodore-64.ttf"), std::to_string(framerate), sf::Color::White, 30, sf::Vector2f(42, 50));
            }
            void update(sfs::Scene &) noexcept
            {
                _frameNumber->setString(std::to_string(framerate));
            }
            void lowerFrame(sfs::Scene &scene) noexcept
            {
                if (framerate - 20 <= 20)
                    framerate = 20;
                else
                    framerate -= 20;
                scene.framerate(framerate);
            }
            void augmentFrame(sfs::Scene &scene) noexcept
            {
                if (framerate + 20 >= 200)
                    framerate = 200;
                else
                    framerate += 20;
                scene.framerate(framerate);
            }
            sf::FloatRect getGlobalBounds() noexcept {return _frameRateText->getGlobalBounds();}
        protected:
            sfs::Text *_frameRateText;
            sfs::Button *_decreaseFrameRate;
            sfs::Button *_augmentFrameRate;
            sfs::Text *_frameNumber;
            uint32_t framerate = 120;
    };

    class optionScene : public sfs::UI
    {
        public:
            optionScene() noexcept : _menuBoxName(nullptr), _optionMenuBox(nullptr), _sound(nullptr), _frameRate(nullptr) {};
            void start(sfs::Scene &scene) noexcept {
                _optionMenuBox = &addChild<Background>(scene, "assets/sprites/OptionWindow.png");
                _optionMenuBox->addComponent<PadderW<Background>>(0, *_optionMenuBox);
                _optionMenuBox->addComponent<PadderH<Background>>(0, *_optionMenuBox);

                _menuBoxName = &addChild<Text>(scene, *scene.getAssetFont("assets/fonts/commodore-64.ttf"), "OPTIONS", sf::Vector2f(-1000, -1000), 30);
                _menuBoxName->addComponent<PadderW<Text>>(0, *_menuBoxName);
                _menuBoxName->addComponent<PadderH<Text>>(-204, *_menuBoxName);

                _sound = &addChild<optionSound>(scene);
                _sound->addComponent<PadderW<optionSound>>(0, *_sound);
				_sound->addComponent<PadderH<optionSound>>(-150, *_sound);

                _frameRate = &addChild<optionFrameRate>(scene);
                _frameRate->addComponent<PadderW<optionFrameRate>>(0, *_frameRate);
                _frameRate->addComponent<PadderH<optionFrameRate>>(-50, *_frameRate);

                _resumeButton = &addChild<sfs::Button>(scene, *scene.getAssetTexture("assets/sprites/blank2.png"),
                                                       *scene.getAssetFont("assets/fonts/commodore-64.ttf"),
                                                       sf::Vector2f(-1000, -1000), std::bind(&optionScene::closeOptions, this), "resume", sf::Color::White, 20);
                _resumeButton->setScale(sf::Vector2f(0.5, 0.5));
                _resumeButton->addComponent<PadderW<sfs::Button>>(0, *_resumeButton);
                _resumeButton->addComponent<PadderH<sfs::Button>>(170, *_resumeButton);
            }
            void closeOptions() noexcept
            {
                this->destroy();
            }
        protected:
            Text *_menuBoxName;
            Background *_optionMenuBox;
            optionSound *_sound;
            optionFrameRate *_frameRate;
            sfs::Button *_resumeButton;
    };
}
