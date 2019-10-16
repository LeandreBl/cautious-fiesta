#pragma once

#include <GameObject.hpp>
#include <Button.hpp>
#include <InputBox.hpp>
#include <Offset.hpp>
#include "GameManager.hpp"
#include "Room.hpp"

namespace cf
{
    class roomList : public sfs::GameObject
    {
        public:
            roomList(sfs::Scene &scene) noexcept;
            void createRoom() noexcept;
            void drawButtonCreateRoom(sfs::Scene &scene) noexcept;
            void joinRoom(const std::string &name) noexcept;
            void addRoom(sfs::Scene &scene, const std::string &name, int mul, int players = 0) noexcept;
            void destroyRooms() noexcept;
            float getHeight() noexcept;
            void HideRoom() noexcept;
        protected:
            sfs::Button *_room;
            sfs::Button *_createRoom;
            sfs::InputBox *_box;
            sfs::Sprite *_imageCreationRoom;
            Room *_selectedRoom;
            GameManager *_gameManager;
    };
}