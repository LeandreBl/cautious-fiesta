#include <Offset.hpp>
#include "Chat.hpp"
#include <Padder.hpp>

namespace cf
{
    void Chat::start(sfs::Scene &scene) noexcept
    {
        _font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
        _chatBox = &addChild<sfs::InputBox>(scene, *_font, sf::Vector2f(0, 0), "send message");
        if (_messageQueu == 3) {
            _chatBox->addComponent<PadderB<sfs::InputBox>>(15, *_chatBox);
            _chatBox->addComponent<PadderL<sfs::InputBox>>(0, *_chatBox);
        } else
            _chatBox->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(25, 970));

        _gameManager = scene.getGameObjects<GameManager>()[0];

        scene.subscribe(*this, sf::Event::KeyPressed);
    }

    void Chat::receiveMessage(Serializer &toread) noexcept
    {
        std::string name;
        toread.get(name);
        std::string message;
        toread.get(message);
        message = name + " : " + message;

        sf::Vector2f newPos;
        if (_chatMessages.empty() == true)
            newPos = sf::Vector2f(_chatBox->getPosition().x, _chatBox->getPosition().y - 20);
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
        if (_chatMessages.size() > _messageQueu) {
            _chatMessages.front()->destroy();
            _chatMessages.erase(_chatMessages.begin());
        }
    }

    void Chat::handleSendMessage(Serializer &toread) noexcept
    {
        uint8_t isOk = 0;
        toread.get(isOk);
        _chatBox->toggle(true);
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
