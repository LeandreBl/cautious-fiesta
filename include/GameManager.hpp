#pragma once

#include <iostream>
#include <GameObject.hpp>
#include "Character.hpp"
#include "TcpConnection.hpp"

namespace cf
{
    class GameManager : public sfs::GameObject
    {
        public :
            void start(sfs::Scene &scene) noexcept
            {
              _tcp = &addChild<TcpConnect>(scene);
            }
            Character _character;
            std::string _ip = "";
            TcpConnect *_tcp = nullptr;
    };
}