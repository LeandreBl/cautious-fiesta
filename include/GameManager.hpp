#pragma once

#include <GameObject.hpp>
#include <Popup.hpp>
#include "Character.hpp"
#include "TcpConnection.hpp"
#include "UdpConnection.hpp"
#include "Serializer.hpp"
#include "Game.hpp"

namespace cf
{
  class GameManager : public sfs::GameObject
  {
    public :
      void start(sfs::Scene &scene) noexcept;
      void update(sfs::Scene &scene) noexcept;
      void leaveRoomAfterTheGameStarted(Serializer &toread) noexcept;
      Character _character;
      std::string _ip = "";
      TcpConnect *_tcp = nullptr;
      UdpConnect *_udp = nullptr;
      sfs::Popup *_popup = nullptr;
      bool _gameStarted = false;
      Game *_game = nullptr;
    protected:
      bool _gameFinished = false;
  };
}