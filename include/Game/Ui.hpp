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
            GameUi(sfs::Scene &scene) noexcept
            {
                _rectangle = &addComponent<sfs::Rectangle>(sf::Vector2f(10, 10), sf::Vector2f(200, 50), sf::Color::White);
                _chat = &addChild<Chat>(scene, 3);
            }
        protected:
            sfs::Rectangle *_rectangle = nullptr;
            Chat *_chat;
    };
}