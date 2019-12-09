#pragma once

#include <UI.hpp>
#include <BasicShape.hpp>

namespace cf
{
    class UiWeapon : public sfs::UI
    {
        public:
            UiWeapon() noexcept;
            void start(sfs::Scene &scene) noexcept;
            void setUiWeapon(const sf::Texture &texture) noexcept;
            sf::FloatRect getGlobalBounds() {return _box->getGlobalBounds();};
        protected:
            sfs::Sprite *_weapon;
            sfs::Sprite *_box;
    };
}