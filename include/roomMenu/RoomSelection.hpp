#pragma once

#include <Vnavbar.hpp>
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
            sf::Vector2f RoomListPos() noexcept;
        protected:
            sfs::Vnavbar *_scrollBar = nullptr;
            roomList *_createButton;
            sfs::Scene &_scene;
            float lockScrollBar = 0;
    };
}