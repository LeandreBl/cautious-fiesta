#pragma once

#include "Chat.hpp"
#include "Life.hpp"
#include "UiWeapon.hpp"

namespace cf
{
    class GameUi : public sfs::UI
    {
        public:
            GameUi(sfs::Scene &scene) noexcept;
        protected:
            Chat *_chat;
            Life *_life;
            UiWeapon *_weapon;
    };
}