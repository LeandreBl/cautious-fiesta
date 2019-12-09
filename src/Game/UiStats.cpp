#include <Padder.hpp>
#include "UiStats.hpp"
#include "GameManager.hpp"

namespace cf
{
    UiStats::UiStats() noexcept
        : _box(nullptr)
        , _speed(nullptr)
        , _attack(nullptr)
        , _attackSpeed(nullptr)
        , _armor(nullptr)
    {
    }

    void UiStats::start(sfs::Scene &scene) noexcept
    {
        auto gameManager = scene.getGameObjects<GameManager>();
        if (!gameManager.empty()) {
            _box = &addComponent<sfs::Sprite>(*scene.getAssetTexture("local-assets/sprites/Menu/ui/OptionWindow.png"));
            _box->setScale(sf::Vector2f(1.3, 0.5));
            addComponent<PadderB<UiStats>>(-90, *this);
            addComponent<PadderW<UiStats>>(0, *this);

            auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");

            _speed = &addComponent<sfs::Text>(*font, "speed: " + std::to_string((int)gameManager[0]->_character.getSpeed()), sf::Color::White, 16, sf::Vector2f(20, 50));
            _attack = &addComponent<sfs::Text>(*font, "attack: " + std::to_string((int)gameManager[0]->_character.getAttack()), sf::Color::White, 16, sf::Vector2f(20, 100));
            _attackSpeed = &addComponent<sfs::Text>(*font, "att speed: " + std::to_string((int)gameManager[0]->_character.getAttackSpeed()), sf::Color::White, 16, sf::Vector2f(350, 50));
            _armor = &addComponent<sfs::Text>(*font, "armor : " + std::to_string((int)gameManager[0]->_character.getArmor()), sf::Color::White, 16, sf::Vector2f(350, 100));
        }
    }

    void UiStats::changeStats(sfs::Scene &scene) noexcept
    {
        auto gameManager = scene.getGameObjects<GameManager>();
        if (!gameManager.empty()) {
            _speed->setString("speed: " + std::to_string((int)gameManager[0]->_character.getSpeed()));
            _attack->setString("attack: " + std::to_string((int)gameManager[0]->_character.getAttack()));
            _attackSpeed->setString("att speed: " + std::to_string((int)gameManager[0]->_character.getAttackSpeed()));
            _armor->setString("armor: " + std::to_string((int)gameManager[0]->_character.getArmor()));
        }
    }
}