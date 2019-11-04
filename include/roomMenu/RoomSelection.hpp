#pragma once

#include <GameObject.hpp>
#include <Hnavbar.hpp>
#include <vector>
#include <Button.hpp>
#include "RoomList.hpp"

namespace cf
{
    class RoomSelector : public sfs::GameObject
    {
        public :
            RoomSelector(sfs::Scene &scene) noexcept;
            void drawRooms(std::vector<std::pair<uint64_t, std::string>> rooms) noexcept;
            void update(sfs::Scene &) noexcept;
            void destroyRoom() noexcept;
            void updatePlayerInRoom(std::vector<std::pair<uint64_t, std::string>> players, uint8_t ready = 2) noexcept;
            sf::Vector2f RoomListPos() noexcept;
        protected:
            sfs::Hnavbar *_scrollBar = nullptr;
            roomList *_createButton;
            sfs::Scene &_scene;
            float lockScrollBar = 0;
    };
}