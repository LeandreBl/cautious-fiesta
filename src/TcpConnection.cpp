#include "TcpConnection.hpp"
#include "RoomScene.hpp"
#include "Protocole.hpp"

namespace cf 
{
    void TcpConnect::bind(sfs::Scene &scene) noexcept
    {
        auto room = scene.getGameObjects<roomScene>()[0];
        autoBind(cf::LOGIN, &roomScene::handleConnect, room);
        autoBind(cf::LOGOUT, &roomScene::handleDisconnect, room);
        autoBind(cf::CREATE_GAMEROOM, &roomScene::handleCreateRoom, room);
        autoBind(cf::GET_GAMEROOMS_LIST, &roomScene::handleRoomList, room);
        autoBind(cf::JOIN_GAMEROOM, &roomScene::handleJoinRoom, room);
        autoBind(cf::DELETE_GAMEROOM, &roomScene::handleDeleteRoom, room);
        autoBind(cf::LEAVE_GAMEROOM, &roomScene::handleLeaveRoom, room);
        autoBind(cf::GET_GAMEROOM_PLAYERS_LIST, &roomScene::handlePlayerList, room);
        autoBind(cf::TOGGLE_READY, &roomScene::handleToggleReadyState, room);
    }

    void TcpConnect::send(const Serializer &packet) noexcept
    {
        if (_socket.send(packet.getNativeHandle(), packet.getSize()) != sf::Socket::Done)
                return ; //TODO ERROR CO
    }

    int TcpConnect::connect(Character charac, const std::string &ip) noexcept
    {
        Serializer packet;
        if (lock == false) {
            _status = _socket.connect(ip, 2121);
            if (_status != sf::Socket::Done)
                return -84; 
            _socket.setBlocking(false);
            lock = true;
        }
        packet.set(charac.getName());
        packet.set(charac.getStats());
        packet.setHeader(pktType_e::LOGIN);
        send(packet);
        return 0;
    }

    void TcpConnect::disconnect() noexcept 
    {
        Serializer packet;
        packet.setHeader(pktType_e::LOGOUT);
        send(packet);
    }

    void TcpConnect::createRoom(const std::string &roomName) noexcept
    {
        Serializer packet;
        packet.set(roomName);
        packet.setHeader(pktType_e::CREATE_GAMEROOM);
        send(packet);
    }

    void TcpConnect::deleteRoom() noexcept
    {
        Serializer packet;
        packet.setHeader(pktType_e::DELETE_GAMEROOM);
        send(packet);
    }

    void TcpConnect::getRooms() noexcept
    {
        Serializer packet;
        packet.setHeader(pktType_e::GET_GAMEROOMS_LIST);
        send(packet);
    }

    void TcpConnect::joinRoom(const std::string &roomName) noexcept
    {
        Serializer packet;
        packet.set(roomName);
        packet.setHeader(pktType_e::JOIN_GAMEROOM);
        std::cout << roomName << std::endl;
        send(packet);
    }

    void TcpConnect::leaveRoom() noexcept
    {
        Serializer packet;
        packet.setHeader(pktType_e::LEAVE_GAMEROOM);
        send(packet);
    }

    void TcpConnect::toggleReadyState() noexcept
    {
        Serializer packet;
        packet.setHeader(pktType_e::TOGGLE_READY);
        send(packet);
    }

    template <typename... Args>
    void TcpConnect::autoBind(size_t index, Args... args) noexcept
	{
        _callbacks[index] = std::bind(args..., std::placeholders::_1);
	}

    void TcpConnect::update(sfs::Scene &) noexcept
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
        while (_serializer.getSize() >= sizeof(header)) {
            _serializer.get(header);
            header.display();
            if (_serializer.getSize() >= header.getLen() && header.isCorrect() == true)
                _callbacks[header.getType()](_serializer);
            else
                return; //TODO ERROR
        }
    }
}