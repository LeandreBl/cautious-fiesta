#pragma once

#include <GameObject.hpp>
#include <vector>
#include <BasicShape.hpp>

namespace cf
{
    class Room : public sfs::GameObject
    {
        public:
            void start(sfs::Scene &scene) noexcept;
            void setImage(const std::string &name) noexcept;
            void hideImage() noexcept;
            void updatePlayerInRoom(std::vector<std::pair<uint64_t, std::string>> players) noexcept;
            float getImageWidth() const noexcept {return _image->getGlobalBounds().width;};
        protected:
            sfs::Sprite *_image = nullptr;
            sfs::Text *_roomName = nullptr;
            const sf::Font *_font;
    };
}