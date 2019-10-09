#pragma once

#include <GameObject.hpp>
#include <Sound.hpp>
#include "MainMenu.hpp"
#include "MenuBackgrounds.hpp"
#include "GameManager.hpp"

namespace cf {
    class MenuManager : public sfs::GameObject
    {
        public:
            MenuManager() noexcept;
            void start(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &scene) noexcept;
        protected :
            MainMenu *_mainMenu;
            Scroller *_scroller;
            GameManager *_gameManager;
    };
}