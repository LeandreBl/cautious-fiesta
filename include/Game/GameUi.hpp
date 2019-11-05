#pragma once

#include <UI.hpp>
#include <BasicShape.hpp>
#include "Chat.hpp"

namespace cf
{
    class GameUi : public sfs::UI
    {
        public:
            GameUi(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &scene) noexcept;
        protected:
            sfs::Rectangle *_rectangle = nullptr;
            sfs::Sprite *_life = nullptr;
            Chat *_chat = nullptr;
    };
}