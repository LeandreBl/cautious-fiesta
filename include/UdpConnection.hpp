#pragma once

#include <queue>
#include <list>

#include <SFML/Network.hpp>

#include <GameObject.hpp>
#include <Serializer.hpp>

#include "Udp.hpp"

namespace cf {
class GameManager;
class UdpConnect : public sfs::GameObject {
      public:
	UdpConnect(GameManager &manager, const sf::IpAddress &ip, uint16_t port) noexcept;
	uint16_t setPort(uint16_t port, const sf::IpAddress &ip) noexcept;
	void update(sfs::Scene &) noexcept;
	void pushPacket(const Serializer &packet, UdpPrctl::Type type) noexcept;
	void pushAck(const UdpPrctl &header) noexcept;
	void send(const Serializer &packet) noexcept;
	void send(const UdpPrctl &header) noexcept;
	void sendInput(UdpPrctl::inputAction action, UdpPrctl::inputType type) noexcept;
	void executePackets(sfs::Scene &scene) noexcept;
	uint16_t getPort() const noexcept;
	bool isConnected() const noexcept;

      protected:
	void receiveData() noexcept;
	void parseHeaders() noexcept;
	void notifyAck(uint16_t idx) noexcept;
	void sendPackets(sfs::Scene &scene) noexcept;
	template <typename... Args> void autoBind(UdpPrctl::Type type, Args... args)
	{
		_callbacks[static_cast<int>(type)] =
			std::bind(args..., this, std::placeholders::_1, std::placeholders::_2,
				  std::placeholders::_3);
	}
	/* function pointers */
	int spawnHandler(sfs::Scene &scene, GameManager &manager, Serializer &toRead);
	int positionHandler(sfs::Scene &scene, GameManager &manager, Serializer &toRead);
	/* end */
	GameManager &_manager;
	std::function<int(sfs::Scene &, GameManager &, Serializer &)>
		_callbacks[static_cast<int>(UdpPrctl::Type::ACK) + 1];
	uint16_t _port;
	sf::IpAddress _ip;
	sf::UdpSocket _socket;
	Serializer _serializer;
	uint16_t _queueIndex;
	int32_t _serverIndex;
	std::list<std::pair<UdpPrctl, Serializer>> _packets;
	std::queue<UdpPrctl> _ackQueue;
	std::queue<std::pair<UdpPrctl, Serializer>> _toProcess;
	float _prev = 0;
	bool _connected;
};
} // namespace cf