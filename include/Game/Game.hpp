#pragma once

#include <GameObject.hpp>
#include "Option.hpp"
#include "SoundManager.hpp"
#include "Ui.hpp"

namespace cf
{
    class Game : public sfs::GameObject
    {
        public:
            Game(sfs::Scene &scene) noexcept;
            void start(sfs::Scene &scene) noexcept;
            void onEvent(sfs::Scene &scene, const sf::Event &event) noexcept;
            void quitGame(sfs::Scene &scene, bool quit) noexcept;
        protected:
            optionScene *_options = nullptr;
            SoundManager *_soundManager = nullptr;
            GameUi *_ui = nullptr;
    };
}