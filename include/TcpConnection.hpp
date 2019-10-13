#pragma once

#include <GameObject.hpp>
#include <SFML/Network.hpp>
#include "Protocole.hpp"
#include "Serializer.hpp"
#include "RoomScene.hpp"

namespace cf {

class TcpConnect : public sfs::GameObject
    {
        public:
            void bind(sfs::Scene &scene) noexcept
            {
                auto room = scene.getGameObjects<roomScene>()[0];
                autoBind(cf::LOGIN, &roomScene::handleConnect, room);
                autoBind(cf::LOGOUT, &roomScene::handleDisconnect, room);
            }
            void connect(const std::string &name, const std::string &ip) noexcept
            {
                Serializer packet;
                if (lock == false) {
                    _status = _socket.connect(ip, 2121);
                    if (_status != sf::Socket::Done)
                        return ; //TODO ERROR CO POPUP 
                    _socket.setBlocking(false);
                    lock = true;
                }
                packet.set(name);
                packet.setHeader(pktType_e::LOGIN);
                if (_socket.send(packet.getNativeHandle(), packet.getSize()) != sf::Socket::Done)
                    return ; //TODO ERROR CO
            }
            void disconnect() noexcept 
            {
                Serializer packet;
                packet.setHeader(pktType_e::LOGOUT);
                if (_socket.send(packet.getNativeHandle(), packet.getSize()) != sf::Socket::Done)
                    return ; //TODO ERROR CO
            }
            void update(sfs::Scene &) noexcept
            {
                char buffer[1024];
                std::size_t rd;
                do {
                    if (_socket.receive(buffer, sizeof(buffer), rd) != sf::Socket::Done)
                        return; //TODO error
                    else
                        _serializer.nativeSet(buffer, rd);
                } while (rd == sizeof(buffer));
                TcpPacketHeader header;
                if (_serializer.getSize() >= sizeof(header)) {
                    _serializer.get(header);
                    if (_serializer.getSize() >= header.getLen() && header.isCorrect() == true)
                        _callbacks[header.getType()](_serializer);
                    else
                        return; //TODO ERROR
                } else
                    return; //TODO ERROR
            }   
            template <typename... Args> void autoBind(size_t index, Args... args)
	        {
         	    _callbacks[index] = std::bind(args..., std::placeholders::_1);
	        }
        protected:
            sf::TcpSocket _socket;
            sf::Socket::Status _status;
            Serializer _serializer;
            std::function<void(Serializer &toRead)> _callbacks[cf::ACK + 1];
            bool lock = false;
    };
}
