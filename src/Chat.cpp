#include "Chat.hpp"

namespace cf
{
    void Chat::start(sfs::Scene &scene) noexcept
    {
        _font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
        _chatBox = &addChild<sfs::InputBox>(scene, *_font, sf::Vector2f(0, 0), "send message");
        _chatBox->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(25, 970));

        _gameManager = scene.getGameObjects<GameManager>()[0];

        scene.subscribe(*this, sf::Event::KeyPressed);
    }

    void Chat::receiveMessage(const std::string &message) noexcept
    {
        sf::Vector2f newPos;
        if (_chatMessages.size() == 0)
            newPos = sf::Vector2f(25, 950);
        else {
            for (auto &i : _chatMessages) {
                auto pos = i->getOffset();
                pos.y -= 25;
                i->setOffset(pos);
            }
            auto pos = _chatMessages[_chatMessages.size() - 1]->getOffset();
            pos.y += 25;
            newPos = pos;
        }
        _chatMessages.emplace_back(&addComponent<sfs::Text>(*_font, message, sf::Color::White, 20, newPos));
        if (_chatMessages.size() > 10) {
            _chatMessages.front()->destroy();
            _chatMessages.erase(_chatMessages.begin());
        }
    }

    void Chat::eraseChat() noexcept
    {
        for (auto &i : _chatMessages)
            i->destroy();
        _chatMessages.clear();
    }

    void Chat::onEvent(sfs::Scene &, const sf::Event &event) noexcept
    {
        if (event.type == sf::Event::KeyPressed) {
		    if (event.key.code == sf::Keyboard::Return && _chatBox->getSelected() == true) {
                _chatBox->toggle(false);
               _gameManager->_tcp->sendMessage(_chatBox->string());
                _chatBox->string("");
            }
        }
    }
}
