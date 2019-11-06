#pragma once

#include "GameManager.hpp"

namespace cf
{
    class InputHandler : public sfs::GameObject
    {
        public:
            void start(sfs::Scene &scene) noexcept;
            void onEvent(sfs::Scene &scene, const sf::Event &event) noexcept;
            void setDefaultKeys() noexcept;
            void setEvtKey(const sf::Event::EventType type, int key, enum UdpPrctl::inputType value) noexcept;
            enum UdpPrctl::inputType getEvtKey(sf::Event::EventType type, int key) noexcept;
        protected:
            GameManager *_gameManager;
            std::vector<std::vector<enum UdpPrctl::inputType>> _evtsMatrix;
    };
}