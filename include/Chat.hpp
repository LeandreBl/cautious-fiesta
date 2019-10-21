#pragma once

#include <GameObject.hpp>
#include <InputBox.hpp>
#include <Offset.hpp>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"

namespace cf
{
    class Chat : public sfs::GameObject
    {
        public:
            void start(sfs::Scene &scene) noexcept;
            void receiveMessage(const std::string &message) noexcept;
            void eraseChat() noexcept;
            void onEvent(sfs::Scene &, const sf::Event &event) noexcept;
        protected:
            sfs::InputBox *_chatBox;
            GameManager *_gameManager;
            std::vector<sfs::Text *> _chatMessages;
            const sf::Font *_font;
    };
}
