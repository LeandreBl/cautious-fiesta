#pragma once

#include <iostream>
#include <GameObject.hpp>
#include "Character.hpp"

namespace cf
{
    class GameManager : public sfs::GameObject
    {
        public :
            Character _character;
            std::string _ip = "";
    };
}