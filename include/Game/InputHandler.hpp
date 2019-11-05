#pragma once

#include "GameManager.hpp"

namespace cf
{
    class InputHandler : public sfs::GameObject
    {
        public:
            void start(sfs::Scene &scene) noexcept;
            void onEvent(sfs::Scene &scene, const sf::Event &event) noexcept;
        protected:
            GameManager *_gameManager;
    };
}