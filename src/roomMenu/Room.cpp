#include <Offset.hpp>
#include "Room.hpp"

namespace cf
{
    void Room::start(sfs::Scene &scene) noexcept
    {
        setPosition(sf::Vector2f(-1500, -1500));
        auto texture = scene.getAssetTexture("local-assets/sprites/Menu/ui/OptionWindow.png");
        auto texture2 = scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png");
        _font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
        _image = &addComponent<sfs::Sprite>(*texture);
        _image->setScale(sf::Vector2f(2.5, 2.39));
        _roomName = &addComponent<sfs::Text>(*_font, "", sf::Color::White, 50, sf::Vector2f(200, 40));

        _toggleReady = &addChild<sfs::Button>(scene, *texture2, *_font, sf::Vector2f(-1000, -1000),
		                                std::bind(&Room::togglePlayerReadyState, this, std::ref(scene)),
		                                "ready", sf::Color::White, 20);
        auto pos = (_image->getGlobalBounds().width / 2) - (_toggleReady->getGlobalBounds().width / 2);
        _toggleReady->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(pos, 150));

        _players = &addComponent<sfs::Text>(*_font, "", sf::Color::White, 50, sf::Vector2f(200, 300));

        _chat = &addChild<Chat>(scene);
        _chat->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(0, 0));
    }

    void Room::setImage() noexcept
    {
        setPosition(sf::Vector2f(0, 0));
    }

    void Room::hideImage() noexcept
    {
        setPosition(sf::Vector2f(-1500, -1500));
        _chat->eraseChat();
        _roomOwner = "";
    }

    void Room::togglePlayerReadyState(sfs::Scene &scene) noexcept
    {
        auto gameManager = scene.getGameObjects<GameManager>()[0];
        gameManager->_tcp->toggleReadyState();
    }

    void Room::handleTogglePlayerReadyState(Serializer &toread) noexcept
    {
        uint8_t state = 0;
        toread.get(state);
        if ((int)state == 0) {
            isready = false;
            _toggleReady->setText("ready");
        }
        else if ((int)state == 1) {
            isready = true;
            _toggleReady->setText("unready");
        }
    }

    void Room::handlePlayerList(Serializer &toread) noexcept
    {
        uint8_t isOk = 0;
        toread.get(isOk);
        if ((int)isOk == 0)
            return;
        std::string roomName;
        toread.get(roomName);

        _roomName->setString(roomName);
        auto pos = (_image->getGlobalBounds().width / 2) - (_roomName->getGlobalBounds().width / 2);
        _roomName->setOffset(sf::Vector2f(pos, 40));

        uint64_t size;
        toread.get(size);
        std::string name;
        std::string text;
        for (uint64_t i = 0; i != size; i+= 1) {
            toread.get(isOk);
            toread.get(name);
            if (i == 0)
                _roomOwner = name;
            text += name;
            text += " state : ";
            text += std::to_string(isOk);
            text += "\n\n";
        }
        _players->setString(text);
        pos = (_image->getGlobalBounds().width / 2) - (_players->getGlobalBounds().width / 2);
        _players->setOffset(sf::Vector2f(pos, _players->getOffset().y));
    }
}