#pragma once

#include <GameObject.hpp>
#include <Button.hpp>
#include <Hnavbar.hpp>
#include "PaddedSprite.hpp"
#include "Character.hpp"
#include "Serializer.hpp"
#include "RoomSelection.hpp"

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
            void handleCreateRoom(Serializer &toread) noexcept {
                uint8_t test = 0;
                toread.get(test);
                std::cout << "create room" << (int)test << std::endl;
            }
            void handleRoomList(Serializer &toread) noexcept {
                uint64_t size = 0;
                uint64_t nbPlayers;
                std::string roomName;
                toread.get(size);
                for (uint64_t i = 0; i != size; i += 1) {
                    toread.get(nbPlayers);
                    toread.get(roomName);
                    std::cout << "il y a "<< nbPlayers << " joueurs dans la room: " << roomName << std::endl;
                }
                std::cout << "jai reçus la liste" << std::endl;
            }
        protected:
            sfs::Button *_backToMenu;
            GameManager *_gameManager;
            RoomSelector *_RSelector;
    };    
}