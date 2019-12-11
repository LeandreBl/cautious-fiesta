#include <Padder.hpp>
#include "UiStats.hpp"
#include "GameManager.hpp"

namespace cf
{
    UiStats::UiStats(uint64_t id) noexcept
        : _box(nullptr)
        , _speed(nullptr)
        , _attack(nullptr)
        , _attackSpeed(nullptr)
        , _armor(nullptr)
        , _id(id)
    {
    }

    void UiStats::start(sfs::Scene &scene) noexcept
    {
        auto gameManager = scene.getGameObjects<GameManager>();
        if (!gameManager.empty()) {
            auto _stats = gameManager[0]->_character.getStats();
            _box = &addComponent<sfs::Sprite>(*scene.getAssetTexture("local-assets/sprites/Menu/ui/OptionWindow.png"));
            _box->setScale(sf::Vector2f(1.3, 0.5));
            addComponent<PadderB<UiStats>>(-90, *this);
            addComponent<PadderW<UiStats>>(0, *this);

            auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
            _speed = &addComponent<sfs::Text>(*font, "speed: " + std::to_string((int)_stats.speed), sf::Color::White, 16, sf::Vector2f(20, 50));
            _attack = &addComponent<sfs::Text>(*font, "attack: " + std::to_string((int)_stats.attack), sf::Color::White, 16, sf::Vector2f(20, 100));
            _attackSpeed = &addComponent<sfs::Text>(*font, "att speed: " + std::to_string((int)_stats.attackSpeed), sf::Color::White, 16, sf::Vector2f(350, 50));
            _armor = &addComponent<sfs::Text>(*font, "armor : " + std::to_string((int)_stats.armor), sf::Color::White, 16, sf::Vector2f(350, 100));
            _kills = &addComponent<sfs::Text>(*font, "kills : 0", sf::Color::White, 16, sf::Vector2f(1110, -820));
        }
    }

    void UiStats::changeStats(sfs::Scene &scene, float to_add, uint64_t id) noexcept
    {
        if (_id == id + 1000) {
        auto gameManager = scene.getGameObjects<GameManager>();
        if (!gameManager.empty()) {
            auto _stats = gameManager[0]->_character.getStats();
            _speed->setString("speed: " + std::to_string((int)(_stats.speed + to_add)));
            _attack->setString("attack: " + std::to_string((int)(_stats.attack + to_add)));
            _attackSpeed->setString("att speed: " + std::to_string((int)(_stats.attackSpeed + to_add)));
            _armor->setString("armor: " + std::to_string((int)(_stats.armor + to_add)));
        }
        }
    }

    void UiStats::changeKills(float kills, uint64_t id) noexcept
    {
        if (_id == id + 1000) {
            _kills->setString("kills : " + std::to_string((int)kills));
        }
    }
}