#include "UdpConnection.hpp"

namespace cf {

UdpConnect::UdpConnect(GameManager &manager, const sf::IpAddress &ip, uint16_t port) noexcept
	: _manager(manager)
	, _callbacks()
	, _port(port)
	, _ip(ip)
	, _socket()
	, _serializer()
	, _queueIndex(0)
	, _serverIndex(-1)
	, _packets()
	, _toProcess()
	, _connected(false)
{
	autoBind(UdpPrctl::Type::SPAWN, &UdpConnect::spawnHandler);
	autoBind(UdpPrctl::Type::POSITION, &UdpConnect::positionHandler);
	setPort(port, ip);
}

bool UdpConnect::isConnected() const noexcept
{
	return _connected;
}

uint16_t UdpConnect::getPort() const noexcept
{
	return _socket.getLocalPort();
}

void UdpConnect::send(const Serializer &packet) noexcept
{
	if (_socket.send(packet.getNativeHandle(), packet.getSize(), _ip, _port)
	    != sf::Socket::Done)
		std::cerr << "error can't send to " << _ip << ":" << _port << std::endl;
}

void UdpConnect::send(const UdpPrctl &header) noexcept
{
	if (_socket.send(&header.getNativeHandle(), sizeof(header), _ip, _port) != sf::Socket::Done)
		std::cerr << "error can't send to " << _ip << ":" << _port << std::endl;
}

uint16_t UdpConnect::setPort(uint16_t port, const sf::IpAddress &ip) noexcept
{
	_port = port;
	_ip = ip;
	if (_socket.bind(port) != sf::Socket::Done) {
		if (_socket.bind(0) != sf::Socket::Done)
			return 0;
		_socket.setBlocking(false);
		std::cout << "Local port created : " << _socket.getLocalPort() << std::endl;
		_connected = true;
		return _socket.getLocalPort();
	}
	_socket.setBlocking(false);
	_connected = true;
	return _socket.getLocalPort();
}

void UdpConnect::pushAck(const UdpPrctl &header) noexcept
{
	_ackQueue.emplace(UdpPrctl::Type::ACK, 0, header.getIndex());
}

void UdpConnect::pushPacket(const Serializer &packet, UdpPrctl::Type type) noexcept
{
	_packets.emplace_back(UdpPrctl(type, packet.getSize(), _queueIndex), packet);
	_queueIndex++;
}

void UdpConnect::sendInput(UdpPrctl::inputAction action, UdpPrctl::inputType type) noexcept
{
	UdpPrctl::udpInput input = {(int)action, (int)type};
	Serializer packet;

	packet << input;
	pushPacket(packet, UdpPrctl::Type::INPUT);
}

void UdpConnect::receiveData() noexcept
{
	sf::IpAddress ip = _ip;
	uint16_t port = _port;
	char data[4096];
	size_t rd;

	do {
		auto ret = _socket.receive(data, sizeof(data), rd, ip, port);
		if (ret == sf::Socket::Disconnected) {
			std::cerr << "Server udp disconnected" << std::endl;
			return;
		}
		else if (ret == sf::Socket::Error) {
			std::cerr << "Error reading udp socket" << std::endl;
			return;
		}
		else if (ip.toInteger() != 0 && ip.toInteger() != 2130706433
			 && (ip != _ip || port != _port)) {
			std::cerr << "Unhandled remote: " << ip << ":" << port << std::endl;
			return;
		}
		_serializer.nativeSet(data, rd);
	} while (rd > 0);
}

void UdpConnect::notifyAck(uint16_t idx) noexcept
{
	for (auto it = _packets.begin(); it != _packets.end(); ++it) {
		if (it->first.getIndex() == idx) {
			_packets.erase(it);
			return;
		}
	}
}

void UdpConnect::parseHeaders() noexcept
{
	if (_serializer.getSize() < sizeof(UdpPrctl))
		return;
	UdpPrctl packet;
	_serializer >>= packet;
	if (packet.isCorrect() == false) {
		_serializer.clear();
		return;
	}
	else if (packet.getType() == UdpPrctl::Type::ACK) {
		notifyAck(packet.getIndex());
		_serializer.shift(sizeof(UdpPrctl));
		return parseHeaders();
	}
	if (abs(packet.getIndex() - _serverIndex) > 1000) {
		_serverIndex = packet.getIndex();
	}
	if (_serializer.getSize() < (packet.getLength() + sizeof(UdpPrctl)))
		return;
	_serializer.shift(sizeof(UdpPrctl));
	pushAck(packet);
	if (packet.getIndex() < _serverIndex) {
		_serializer.shift(packet.getLength());
	}
	else {
		_toProcess.emplace(packet, Serializer(_serializer, packet.getLength()));
		_serverIndex = packet.getIndex();
	}
	return parseHeaders();
}

void UdpConnect::executePackets(sfs::Scene &scene) noexcept
{
	while (!_toProcess.empty()) {
		auto &p = _toProcess.front();
		int idx = static_cast<int>(p.first.getType());
		if (_callbacks[idx])
			_callbacks[idx](scene, _manager, p.second);
		_toProcess.pop();
	}
}

void UdpConnect::sendPackets(sfs::Scene &scene) noexcept
{
	float time = scene.realTime();

	if (time - _prev > (1.f / 60)) {
		while (!_ackQueue.empty()) {
			auto &p = _ackQueue.front();
			send(p);
			_ackQueue.pop();
		}
		for (auto &&i : _packets) {
			Serializer s;
			s << i.first;
			s << i.second;
			send(s);
		}
		_prev = time;
	}
}

void UdpConnect::update(sfs::Scene &scene) noexcept
{
	receiveData();
	parseHeaders();
	executePackets(scene);
	sendPackets(scene);
}
} // namespace cf
