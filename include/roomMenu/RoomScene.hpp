#pragma once

#include <Button.hpp>
#include <GameObject.hpp>
#include "Serializer.hpp"
#include "GameManager.hpp"
#include "RoomSelection.hpp"

namespace cf
{
    class roomScene : public sfs::GameObject
    {
        public:
            void start(sfs::Scene &scene) noexcept;
            void deleteScene() noexcept;
            void handleConnect(Serializer &toread) noexcept;
            void handleDisconnect(Serializer &toread) noexcept;
            void handleCreateRoom(Serializer &toread) noexcept;
            void handleDeleteRoom(Serializer &toread) noexcept; // TODO faire la disparition de la room pour les autres joeurs
            void handleRoomList(Serializer &toread) noexcept;
            void handleJoinRoom(Serializer &toread) noexcept;
            void handleLeaveRoom(Serializer &toread) noexcept;
            void handlePlayerList(Serializer &toread) noexcept;
            void handleToggleReadyState(Serializer &toread) noexcept;
        protected:
            sfs::Button *_backToMenu;
            GameManager *_gameManager;
            RoomSelector *_RSelector;
    };    
}
