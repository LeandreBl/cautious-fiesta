#include "InputHandler.hpp"
#include "Udp.h"

namespace cf
{

    void InputHandler::start(sfs::Scene &scene) noexcept
    {
        _gameManager = scene.getGameObjects<GameManager>()[0];
        scene.subscribe(*this, sf::Event::KeyPressed);
        scene.subscribe(*this, sf::Event::KeyReleased);
        scene.subscribe(*this, sf::Event::MouseButtonPressed);
        scene.subscribe(*this, sf::Event::MouseButtonReleased);
        setDefaultKeys();
    }

    void InputHandler::onEvent(sfs::Scene &, const sf::Event &event) noexcept
    {
        if (event.type == sf::Event::KeyPressed) {
            if (getEvtKey(event.type, event.key.code) != UdpPrctl::inputType::UNKNOWN_KEY)
                _gameManager->_udp->sendInput(UdpPrctl::inputType::PRESSED, getEvtKey(event.type, event.key.code));
        } else if (event.type == sf::Event::KeyReleased) {
            if (getEvtKey(event.type, event.key.code) != UdpPrctl::inputType::UNKNOWN_KEY)
                _gameManager->_udp->sendInput(UdpPrctl::inputType::RELEASED, getEvtKey(event.type, event.key.code));
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (getEvtKey(event.type, event.mouseButton.button) != UdpPrctl::inputType::UNKNOWN_KEY)
                _gameManager->_udp->sendInput(UdpPrctl::inputType::PRESSED, getEvtKey(event.type, event.mouseButton.button));
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (getEvtKey(event.type, event.mouseButton.button) != UdpPrctl::inputType::UNKNOWN_KEY)
                _gameManager->_udp->sendInput(UdpPrctl::inputType::RELEASED, getEvtKey(event.type, event.mouseButton.button));
        }
    }

    void InputHandler::setDefaultKeys() noexcept
    {
        setEvtKey(sf::Event::EventType::KeyPressed, sf::Keyboard::Q, UdpPrctl::inputType::LEFT);
        setEvtKey(sf::Event::EventType::KeyReleased, sf::Keyboard::Q, UdpPrctl::inputType::LEFT);
        setEvtKey(sf::Event::EventType::KeyPressed, sf::Keyboard::D, UdpPrctl::inputType::RIGHT);
        setEvtKey(sf::Event::EventType::KeyReleased, sf::Keyboard::D, UdpPrctl::inputType::RIGHT);
        setEvtKey(sf::Event::EventType::KeyPressed, sf::Keyboard::Z, UdpPrctl::inputType::UP);
        setEvtKey(sf::Event::EventType::KeyReleased, sf::Keyboard::Z, UdpPrctl::inputType::UP);
        setEvtKey(sf::Event::EventType::KeyPressed, sf::Keyboard::S, UdpPrctl::inputType::DOWN);
        setEvtKey(sf::Event::EventType::KeyReleased, sf::Keyboard::S, UdpPrctl::inputType::DOWN);
        setEvtKey(sf::Event::EventType::MouseButtonPressed, sf::Mouse::Button::Left, UdpPrctl::inputType::ATTACK1);
        setEvtKey(sf::Event::EventType::MouseButtonReleased, sf::Mouse::Button::Left, UdpPrctl::inputType::ATTACK1);
        setEvtKey(sf::Event::EventType::MouseButtonPressed, sf::Mouse::Button::Right, UdpPrctl::inputType::ATTACK2);
        setEvtKey(sf::Event::EventType::MouseButtonReleased, sf::Mouse::Button::Right, UdpPrctl::inputType::ATTACK2);
    }

    void InputHandler::setEvtKey(sf::Event::EventType type, int key, enum UdpPrctl::inputType value) noexcept
    {
        if (type >= _evtsMatrix.size())
            _evtsMatrix.resize(type + 1);
        if (key >= (int)_evtsMatrix[type].size())
            _evtsMatrix[type].resize(key + 1, UdpPrctl::inputType::UNKNOWN_KEY);
        _evtsMatrix[type][key] = value;
    }

    enum UdpPrctl::inputType InputHandler::getEvtKey(sf::Event::EventType type, int key) noexcept
    {
        if (type >= _evtsMatrix.size() || key >= (int)_evtsMatrix[type].size())
            return UdpPrctl::inputType::UNKNOWN_KEY;
        return _evtsMatrix[type][key];
    }
}