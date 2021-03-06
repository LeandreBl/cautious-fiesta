#pragma once

#include <Serializer.hpp>
#include "RoomList.hpp"
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
            void handleGameStart(Serializer &toread) noexcept;
            void handleAssetRequirement(Serializer &toread) noexcept;
            void handleLoadAsset(Serializer &toread) noexcept;
        protected:
            sfs::Button *_backToMenu;
            GameManager *_gameManager;
            roomList *_roomList;
            sfs::Scene &_scene;
            std::vector<std::string> _assetsPath;
            bool _checkAssets = false;
            bool ConnectionError = false;
    };
}
