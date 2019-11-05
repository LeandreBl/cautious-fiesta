#pragma once

#include <GameObject.hpp>
#include <functional>
#include <SFML/Network.hpp>
#include "Serializer.hpp"
#include "Character.hpp"

namespace cf {

class TcpConnect : public sfs::GameObject
    {
        public:
            void bind(sfs::Scene &scene) noexcept;
            void bindAfterGameStarted(sfs::Scene &scene) noexcept;
            void send(const Serializer &packet) noexcept;
            int connect(Character charac, const std::string &ip) noexcept;
            void disconnect() noexcept;
            void createRoom(const std::string &roomName) noexcept;
            void deleteRoom() noexcept;
            void getRooms() noexcept;
            void joinRoom(const std::string &roomName) noexcept;
            void leaveRoom() noexcept;
            void toggleReadyState() noexcept;
            void sendMessage(const std::string &message) noexcept;
            void loadAsset(const std::string &asset) noexcept;
            void AssetRequirementIsDone() noexcept;
            void update(sfs::Scene &) noexcept;  
            template <typename... Args>
            void autoBind(size_t index, Args... args) noexcept;
        protected:
            sf::TcpSocket _socket;
            sf::Socket::Status _status;
            Serializer _serializer;
            std::function<void(Serializer &toRead)> _callbacks[cf::ACK + 1];
            bool lock = false;
    };
}