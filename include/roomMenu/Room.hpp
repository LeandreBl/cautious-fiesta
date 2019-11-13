#pragma once

#include <Button.hpp>
#include "Chat.hpp"
#include "Serializer.hpp"

namespace cf
{
    class Room : public sfs::GameObject
    {
        public:
            void start(sfs::Scene &scene) noexcept;
            void setImage(const std::string &name) noexcept;
            void hideImage() noexcept;
            float getImageWidth() const noexcept {return _image->getGlobalBounds().width;};
            void togglePlayerReadyState(sfs::Scene &scene) noexcept;
            void handleTogglePlayerReadyState(Serializer &toread) noexcept;
            void handlePlayerList(Serializer &toread) noexcept;
            std::string getRoomOwner() const noexcept {return _roomOwner;};
        protected:
            sfs::Sprite *_image = nullptr;
            sfs::Text *_roomName = nullptr;
            sfs::Button *_toggleReady = nullptr;
            sfs::Text *_players = nullptr;
            Chat *_chat;
            const sf::Font *_font;
            bool isready = false;
            std::string _roomOwner;
    };
}