#include "Room.hpp"
#include "GameManager.hpp"
#include <Offset.hpp>

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

    void Room::setImage(const std::string &name) noexcept
    {
        _roomName->setString(name);
        auto pos = (_image->getGlobalBounds().width / 2) - (_roomName->getGlobalBounds().width / 2);
        _roomName->setOffset(sf::Vector2f(pos, 40));
        setPosition(sf::Vector2f(0, 0));
    }

    void Room::hideImage() noexcept
    {
        setPosition(sf::Vector2f(-1500, -1500));
        _chat->eraseChat();
    }

    void Room::updatePlayerInRoom(std::vector<std::pair<uint64_t, std::string>> players, uint8_t ready) noexcept
    {
        if ((int)ready == 0) {
            isready = false;
            _toggleReady->setText("ready");
        }
        else if ((int)ready == 1) {
            isready = true;
            _toggleReady->setText("unready");
        }
        else if ((int)ready == 2) {
            std::string text;
            for (auto &i : players) {
                text += i.second;
                text += " state : ";
                text += std::to_string(i.first);
                text += "\n\n";
            }
            _players->setString(text);
            auto pos = (_image->getGlobalBounds().width / 2) - (_players->getGlobalBounds().width / 2);
            _players->setOffset(sf::Vector2f(pos, _players->getOffset().y));
        }
    }

    void Room::togglePlayerReadyState(sfs::Scene &scene) noexcept
    {
        auto gameManager = scene.getGameObjects<GameManager>()[0];
        gameManager->_tcp->toggleReadyState();
    }
}