#pragma once

#include <InputBox.hpp>
#include "Room.hpp"

namespace cf
{
    class roomList : public sfs::GameObject
    {
        public:
            roomList(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &scene) noexcept;
            void createRoom() noexcept {_gameManager->_tcp->createRoom(_box->string());};
            void drawButtonCreateRoom(sfs::Scene &scene) noexcept;
            void addRoom(sfs::Scene &scene, const std::string &name, int mul, int players = 0) noexcept;
            void destroyRooms() noexcept;
            float getHeight() noexcept;
            void handleJoinRoom(Serializer &toread) noexcept;
            void handleLeaveRoom(Serializer &toread) noexcept;
            void handleCreateRoom(Serializer &toread) noexcept;
            void handleDeleteRoom(Serializer &toread) noexcept;
        protected:
            sfs::Button *_room;
            sfs::Button *_createRoom;
            sfs::Button *_deleteRoom;
            sfs::InputBox *_box;
            sfs::Sprite *_imageCreationRoom;
            Room *_selectedRoom;
            GameManager *_gameManager;
    };
}