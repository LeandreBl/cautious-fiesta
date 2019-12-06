#pragma once

#include "MainMenu.hpp"
#include "MenuBackgrounds.hpp"
#include "GameManager.hpp"
#include "SoundManager.hpp"
#include "RoomScene.hpp"

namespace cf {
    class MenuManager : public sfs::GameObject
    {
        public:
            MenuManager() noexcept;
            void start(sfs::Scene &scene) noexcept;
            void onEvent(sfs::Scene &scene, const sf::Event &event) noexcept;
            Scroller *getScroller() const noexcept {return _scroller;};
        protected :
            MainMenu *_mainMenu;
            Scroller *_scroller;
            GameManager *_gameManager;
            SoundManager *_soundManager;
            roomScene *_roomScene;
    };
}