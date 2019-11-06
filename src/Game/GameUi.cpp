#include "GameUi.hpp"

namespace cf
{
    GameUi::GameUi(sfs::Scene &scene) noexcept
    {
        _chat = &addChild<Chat>(scene, 3);
        auto life = &addComponent<sfs::Sprite>(*scene.getAssetTexture("tmp/life.png"));
        life->setScale(sf::Vector2f(2, 1.5));
        _rectangle = &addComponent<sfs::Rectangle>(sf::Vector2f(392, 50), sf::Vector2f(0, 30), sf::Color::Black);

        auto projectile = &addComponent<sfs::Sprite>(*scene.getAssetTexture("tmp/Projectiles.png"), sf::Vector2f(300, 300));
        sf::IntRect test = projectile->getTextureRect();
        test.height = projectile->getTextureRect().height / 4;
        projectile->setTextureRect(test);
        projectile->setScale(sf::Vector2f(3,3));

        _life = &addComponent<sfs::Sprite>(*scene.getAssetTexture("tmp/lifeHeart.png"), sf::Vector2f(500, 500));
        _life->setScale(sf::Vector2f(4,4));

    }

    void GameUi::update(sfs::Scene &) noexcept
    {
        if (_rectangle->getSize().x > -230)
            _rectangle->setSize(sf::Vector2f(_rectangle->getSize().x - 1, 50));
    }
}