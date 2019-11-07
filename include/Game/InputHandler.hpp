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
            void changeKeyDetection(bool mode, UdpPrctl::inputType type) noexcept;
            void changeGameStarted(bool mode) noexcept {_gameIsStarted = mode;};
            bool getKeyboardActive() noexcept {return _optionKeyboardIsActive;};
            enum UdpPrctl::inputType getEvtKey(sf::Event::EventType type, int key) noexcept;
            std::vector<std::vector<enum UdpPrctl::inputType>> getMatrix() noexcept {return _evtsMatrix;};
        protected:
            GameManager *_gameManager;
            std::vector<std::vector<enum UdpPrctl::inputType>> _evtsMatrix;
            bool _optionKeyboardIsActive = false;
            UdpPrctl::inputType _tmpType;
            bool _gameIsStarted = false;
    };
}