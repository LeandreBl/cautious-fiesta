#include "Room.hpp"
#include "GameManager.hpp"
#include <Offset.hpp>

namespace cf
{
    void Room::start(sfs::Scene &scene) noexcept
    {
        setPosition(sf::Vector2f(-1500, -1500));
        auto texture = scene.getAssetTexture("assets/sprites/Menu/ui/OptionWindow.png");
        auto texture2 = scene.getAssetTexture("assets/sprites/Menu/ui/BlankButton2.png");
        _font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
        _image = &addComponent<sfs::Sprite>(*texture);
        _image->setScale(sf::Vector2f(2.5, 2.39));
        _roomName = &addComponent<sfs::Text>(*_font, "", sf::Color::White, 50, sf::Vector2f(200, 40));

        _toggleReady = &addChild<sfs::Button>(scene, *texture2, *_font, sf::Vector2f(-1000, -1000),
		                                std::bind(&Room::togglePlayerReadyState, this, std::ref(scene)),
		                                "ready", sf::Color::White, 20);
        auto pos = (_image->getGlobalBounds().width / 2) - (_toggleReady->getGlobalBounds().width / 2);
        _toggleReady->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(pos, 150));
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
    }

    void Room::updatePlayerInRoom(std::vector<std::pair<uint64_t, std::string>> players, uint8_t ready) noexcept //TODO FINIR
    {
        if ((int)ready == 0)
            isready = false;
        else if ((int)ready == 1)
            isready = true;
        else if ((int)ready == 2) {
            addComponent<sfs::Text>(*_font, players[0].second, sf::Color::White, 50, sf::Vector2f(200, 200));
        }
    }

    void Room::togglePlayerReadyState(sfs::Scene &scene) noexcept
    {
        auto gameManager = scene.getGameObjects<GameManager>()[0];
        gameManager->_tcp->toggleReadyState();
        if (isready == false)
            _toggleReady->setText("unready");
        else if (isready == true)
            _toggleReady->setText("ready");
    }
}