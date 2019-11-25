#pragma once

#include <InputBox.hpp>
#include "GameManager.hpp"

namespace cf
{
    class Chat : public sfs::GameObject
    {
        public:
            Chat(int messageQueu = 10) noexcept {_messageQueu = messageQueu;};
            void start(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &scene) noexcept;
            void receiveMessage(Serializer &toread) noexcept;
            void handleSendMessage(Serializer &toread) noexcept;            
            void eraseChat() noexcept;
            void onEvent(sfs::Scene &, const sf::Event &event) noexcept;
        protected:
            sfs::InputBox *_chatBox;
            GameManager *_gameManager;
            std::vector<sfs::Text *> _chatMessages;
            const sf::Font *_font;
            size_t _messageQueu;
    };
}
