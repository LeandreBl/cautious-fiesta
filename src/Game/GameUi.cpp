#include "GameUi.hpp"

namespace cf
{
    GameUi::GameUi(sfs::Scene &scene) noexcept
    {
        _chat = &addChild<Chat>(scene, 3);
        auto _life = &addComponent<sfs::Sprite>(*scene.getAssetTexture("life.png"));
        _life->setScale(sf::Vector2f(2, 1.5));
        _rectangle = &addComponent<sfs::Rectangle>(sf::Vector2f(392, 50), sf::Vector2f(0, 30), sf::Color::Black);
    }

    void GameUi::update(sfs::Scene &scene) noexcept
    {
        if (_rectangle->getSize().x > -230)
            _rectangle->setSize(sf::Vector2f(_rectangle->getSize().x - 1, 50));
    }
}