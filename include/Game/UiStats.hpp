#pragma once

#include <UI.hpp>
#include <BasicShape.hpp>

namespace cf
{
    class UiStats : public sfs::UI
    {
        public:
            UiStats(uint64_t id) noexcept;
            void start(sfs::Scene &scene) noexcept;
            sf::FloatRect getGlobalBounds() const noexcept {return _box->getGlobalBounds();};
            void changeStats(sfs::Scene &scene) noexcept;
            void changeKills(float kills, uint64_t id) noexcept;
        protected:
            sfs::Sprite *_box;
            sf::Text *_speed;
            sf::Text *_attack;
            sf::Text *_attackSpeed;
            sf::Text *_armor;
            sf::Text *_kills;
            uint64_t _id;
    };
}