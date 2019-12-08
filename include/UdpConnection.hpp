#pragma once

#include <queue>
#include <list>
#include <functional>

#include <SFML/Network.hpp>

#include <GameObject.hpp>
#include <Serializer.hpp>

#include "Udp.hpp"

namespace cf {
class GameManager;
class UdpConnect : public sfs::GameObject {
      public:
	UdpConnect(GameManager &manager) noexcept;
	int connect(uint16_t port, const sf::IpAddress &ip) noexcept;
	void update(sfs::Scene &) noexcept;
	void pushPacket(const Serializer &packet, UdpPrctl::Type type) noexcept;
	void sendInput(UdpPrctl::inputAction action, UdpPrctl::inputType type) noexcept;
	bool isConnected() const noexcept;

      protected:
	void executePacket(sfs::Scene &scene, const UdpPrctl &header) noexcept;
	void receiveData(sfs::Scene &scene) noexcept;
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
	int velocityHandler(sfs::Scene &scene, GameManager &manager, Serializer &toRead);
	int destroyHandler(sfs::Scene &scene, GameManager &manager, Serializer &toRead);
	/* end */
	GameManager &_manager;
	std::function<int(sfs::Scene &, GameManager &, Serializer &)>
		_callbacks[static_cast<int>(UdpPrctl::Type::ACK) + 1];
	sf::TcpSocket _socket;
	Serializer _serializer;
	std::queue<Serializer> _toWrite;
	uint16_t _queueIndex;
	bool _connected;
};
} // namespace cf
