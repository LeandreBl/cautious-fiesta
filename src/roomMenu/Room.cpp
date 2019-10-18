#include "Room.hpp"

namespace cf
{
    void Room::start(sfs::Scene &scene) noexcept
    {
        setPosition(sf::Vector2f(-1500, -1500));
        auto texture = scene.getAssetTexture("assets/sprites/Menu/ui/OptionWindow.png");
        _font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
        _image = &addComponent<sfs::Sprite>(*texture);
        _image->setScale(sf::Vector2f(2.5, 2.39));
        _roomName = &addComponent<sfs::Text>(*_font, "", sf::Color::White, 50, sf::Vector2f(200, 40));       
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

    void Room::updatePlayerInRoom(std::vector<std::pair<uint64_t, std::string>> players) noexcept //TODO FINIR
    {
        addComponent<sfs::Text>(*_font, players[0].second, sf::Color::White, 50, sf::Vector2f(200, 200));
    }
}