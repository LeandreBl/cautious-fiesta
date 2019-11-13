#pragma once

#include <GameObject.hpp>
#include <functional>
#include <SFML/Network.hpp>

#include <Tcp.hpp>
#include <Serializer.hpp>

#include "Character.hpp"

namespace cf
{

class TcpConnect : public sfs::GameObject
{
      public:
	TcpConnect(sfs::Scene &scene) noexcept : _scene(scene) {};
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
	void sendLocalPort(uint16_t port) noexcept;
	void update(sfs::Scene &) noexcept;
	template <typename... Args>
	void autoBind(TcpPrctl::Type type, Args... args) noexcept
	{
		_callbacks[static_cast<int>(type)] =
			std::bind(args..., std::placeholders::_1);
	}

      protected:
	sf::TcpSocket _socket;
	sf::Socket::Status _status;
	Serializer _serializer;
	std::function<void(Serializer &toRead)>
		_callbacks[static_cast<int>(TcpPrctl::Type::ACK) + 1];
	bool lock = false;
	sfs::Scene &_scene;
};
} // namespace cf