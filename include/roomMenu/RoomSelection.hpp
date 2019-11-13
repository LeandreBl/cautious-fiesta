#pragma once

#include <Vnavbar.hpp>
#include "RoomList.hpp"

namespace cf
{
    class RoomSelector : public sfs::GameObject
    {
        public :
            RoomSelector(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &) noexcept;
            sf::Vector2f RoomListPos() noexcept;
            void handleRoomList(Serializer &toread) noexcept;
        protected:
            sfs::Vnavbar *_scrollBar = nullptr;
            roomList *_createButton;
            sfs::Scene &_scene;
            float lockScrollBar = 0;
    };
}