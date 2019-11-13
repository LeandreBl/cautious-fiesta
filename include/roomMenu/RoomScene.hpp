#pragma once

#include <Serializer.hpp>
#include "RoomSelection.hpp"
#include "AssetLoader.hpp"

namespace cf
{
    class roomScene : public sfs::GameObject
    {
        public:
            roomScene(sfs::Scene &scene) noexcept;
            void start(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &scene) noexcept;
            void deleteScene() noexcept;
            void handleConnect(Serializer &toread) noexcept;
            void handleDisconnect(Serializer &toread) noexcept;
            void handleCreateRoom(Serializer &toread) noexcept;
            void handleDeleteRoom(Serializer &toread) noexcept;
            void handleRoomList(Serializer &toread) noexcept;
            void handleJoinRoom(Serializer &toread) noexcept;
            void handleLeaveRoom(Serializer &toread) noexcept;
            void handleGameStart(Serializer &toread) noexcept;
            void handleAssetRequirement(Serializer &toread) noexcept;
            void handleLoadAsset(Serializer &toread) noexcept;
        protected:
            sfs::Button *_backToMenu;
            GameManager *_gameManager;
            RoomSelector *_RSelector;
            sfs::Scene &_scene;
            std::vector<std::string> _assetsPath;
            bool _checkAssets = false;
    };
}
