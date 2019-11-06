#pragma once

#include <Popup.hpp>
#include "Character.hpp"
#include "TcpConnection.hpp"
#include "UdpConnection.hpp"
#include <Serializer.hpp>

namespace cf
{
  class GameManager : public sfs::GameObject
  {
    public :
      void start(sfs::Scene &scene) noexcept;
      void update(sfs::Scene &scene) noexcept;
      void disconnectAndLeaveRoom(Serializer &toread) noexcept;
      void updateRooms(Serializer &toread) noexcept;
      Character _character;
      std::string _ip = "";
      TcpConnect *_tcp = nullptr;
      UdpConnect *_udp = nullptr;
      sfs::Popup *_popup = nullptr;
      bool _gameStarted = false;
      bool _gameFinished = false;
  };
}