#pragma once

#include <GameObject.hpp>
#include <Button.hpp>
#include "PaddedSprite.hpp"
#include "Character.hpp"
#include "Serializer.hpp"

namespace cf
{
    //forward declaration
    class GameManager;

    class roomScene : public sfs::GameObject
    {
        public:
            void start(sfs::Scene &scene) noexcept;
            void deleteScene() noexcept;
            void handleConnect(Serializer &toread) noexcept{
                uint8_t test = 0;
                toread.get(test); //TODO popUP
                std::cout << "login" << (int)test << std::endl;
            }
            void handleDisconnect(Serializer &toread) noexcept {
                uint8_t test = 0;
                toread.get(test);
                std::cout << "logout" << (int)test << std::endl;
            }
        protected:
            sfs::Button *_backToMenu;
            GameManager *_gameManager;
    };    
}