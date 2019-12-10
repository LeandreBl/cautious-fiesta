#pragma once

#include <Popup.hpp>
#include <Serializer.hpp>

#include "Character.hpp"
#include "TcpConnection.hpp"
#include "UdpConnection.hpp"

namespace cf {
class GoPlayer;
class GameManager : public sfs::GameObject {
      public:
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;
	void disconnectAndLeaveRoom(Serializer &toread) noexcept;
	void updateRooms(Serializer &toread) noexcept;
	GoPlayer *getNearestPlayer(const sf::Vector2f &pos) noexcept;
	Character _character;
	std::string _ip = "";
	TcpConnect *_tcp = nullptr;
	UdpConnect *_udp = nullptr;
	sfs::Popup *_popup = nullptr;
	GoPlayer *_self = nullptr;
	bool _gameStarted = false;
	bool _gameFinished = false;
	float _kills;
	std::vector<GoPlayer *> _players;
};
} // namespace cf