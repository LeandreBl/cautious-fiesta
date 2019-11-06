#include "UdpConnection.hpp"

namespace cf
{

    void UdpConnect::send(Serializer &packet) noexcept
    {
        if (_socket.send(packet.getNativeHandle(), packet.getSize(), _ip, _port) != sf::Socket::Done)
            std::cout << "error" << std::endl;
    }

    void UdpConnect::setPort(uint16_t port, std::string ip) noexcept
    {
        _port = port;
        _ip = ip;
        if (_socket.bind(port) != sf::Socket::Done)
            std::cout << "fail to bin the udp socket to the port : " << _port << std::endl;
        _socket.setBlocking(false);
    }

    void UdpConnect::sendInput(UdpPrctl::inputType action, UdpPrctl::inputType type) noexcept
    {
        if (action == UdpPrctl::inputType::RELEASED)
            std::cout << "released" << std::endl;
        else
            std::cout << "pressed" << std::endl;

        _queueIndex += 1;
        //_toWrite.emplace(packet); //TODO CREER LE PACKET A ENVOYE, METTRE EN COMMEUN UDP.H ET SERIALIZE.HPP
    }

    void UdpConnect::update(sfs::Scene &) noexcept
    {
        char buffer[1024];
        std::size_t rd;

        if (_queueIndex >= 30000)
            _queueIndex = 0;

        while (_toWrite.empty() == false) {
            Serializer packet = _toWrite.front();
            send(packet);
            _toWrite.pop();
        }

        do {
            if (_socket.receive(buffer, sizeof(buffer), rd, _ip, _port) != sf::Socket::Done)
                return;
            else
                _serializer.nativeSet(buffer, rd);
        } while (rd == sizeof(buffer));
        std::cout << "Received " << rd << " bytes from " << _ip << " on port " << _port << std::endl;
        UdpPrctl::udpHeader header;
        while (_serializer.getSize() >= sizeof(header)) {
            _serializer.get(header);
            UdpPrctl udp(static_cast<UdpPrctl::Type>(header.type), header.length, header.index);
            if (udp.isCorrect())
                std::cout << "packet type = " << static_cast<int>(udp.getType()) << std::endl;
        }
    }
}