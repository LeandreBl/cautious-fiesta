#pragma once

#include <UI.hpp>
#include <BasicShape.hpp>
#include "Chat.hpp"

namespace cf
{

    class Chat;

    class GameUi : public sfs::UI
    {
        public:
            GameUi(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &scene) noexcept;
        protected:
            sfs::Rectangle *_rectangle = nullptr;
            Chat *_chat;
    };
}