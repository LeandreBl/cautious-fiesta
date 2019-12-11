#pragma once

#include "Chat.hpp"
#include "Life.hpp"
#include "UiWeapon.hpp"
#include "UiStats.hpp"

namespace cf
{
    class GameUi : public sfs::UI
    {
        public:
            GameUi(sfs::Scene &scene) noexcept;
        protected:
            Chat *_chat;
            UiWeapon *_weapon;
    };
}