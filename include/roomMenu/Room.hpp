#pragma once

#include <vector>
#include <Button.hpp>
#include <BasicShape.hpp>
#include "Chat.hpp"

namespace cf
{
    class Room : public sfs::GameObject
    {
        public:
            void start(sfs::Scene &scene) noexcept;
            void setImage(const std::string &name) noexcept;
            void hideImage() noexcept;
            void updatePlayerInRoom(std::vector<std::pair<uint64_t, std::string>> players, uint8_t isready) noexcept;
            float getImageWidth() const noexcept {return _image->getGlobalBounds().width;};
            void togglePlayerReadyState(sfs::Scene &scene) noexcept;
        protected:
            sfs::Sprite *_image = nullptr;
            sfs::Text *_roomName = nullptr;
            sfs::Button *_toggleReady = nullptr;
            sfs::Text *_players = nullptr;
            Chat *_chat;
            const sf::Font *_font;
            bool isready = false;
    };
}