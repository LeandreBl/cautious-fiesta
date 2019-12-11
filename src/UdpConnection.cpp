#include "MenuManager.hpp"
#include "InputHandler.hpp"
#include "UdpConnection.hpp"

namespace cf
{

UdpConnect::UdpConnect(GameManager &manager) noexcept
	: _manager(manager), _callbacks(), _socket(), _serializer(), _toWrite(), _queueIndex(0), _connected(false)
{
	autoBind(UdpPrctl::Type::SPAWN, &UdpConnect::spawnHandler);
	autoBind(UdpPrctl::Type::POSITION, &UdpConnect::positionHandler);
	autoBind(UdpPrctl::Type::VELOCITY, &UdpConnect::velocityHandler);
	autoBind(UdpPrctl::Type::DESTROY, &UdpConnect::destroyHandler);
	autoBind(UdpPrctl::Type::ATTACK, &UdpConnect::attackHandler);
	autoBind(UdpPrctl::Type::STATE, &UdpConnect::stateHandler);
}

int UdpConnect::connect(uint16_t port, const sf::IpAddress &ip) noexcept
{
	auto status = _socket.connect(ip, port);
	if (status != sf::Socket::Done)
		return -1;
	_socket.setBlocking(false);
	_connected = true;
	return 0;
}

bool UdpConnect::isConnected() const noexcept
{
	return _connected;
}

void UdpConnect::pushPacket(const Serializer &packet, UdpPrctl::Type type) noexcept
{
	Serializer s;
	s << UdpPrctl(type, packet.getSize(), _queueIndex++);
	s << packet;
	_toWrite.emplace(s);
}

void UdpConnect::sendInput(UdpPrctl::inputAction action, UdpPrctl::inputType type) noexcept
{
	Serializer packet;

	packet << static_cast<int32_t>(action);
	packet << static_cast<int32_t>(type);
	pushPacket(packet, UdpPrctl::Type::INPUT);
}

void UdpConnect::receiveData(sfs::Scene &scene) noexcept
{
	char data[4096];
	size_t rd;

	do
	{
		auto ret = _socket.receive(data, sizeof(data), rd);
		if (ret != sf::Socket::Done)
			return;
		_serializer.nativeSet(data, rd);
	} while (rd == sizeof(data));
}

void UdpConnect::executePacket(sfs::Scene &scene, const UdpPrctl &header) noexcept
{
	int idx = static_cast<int>(header.getType());
	Serializer s(_serializer, header.getLength());
	if (_callbacks[idx])
		_callbacks[idx](scene, _manager, s);
}

static sf::Socket::Status sendWrapper(sf::TcpSocket &socket, void *data, size_t size)
{
	size_t total = 0;

	while (total < size)
	{
		size_t wr;
		auto status = socket.send((char *)data + total, size - total, wr);
		if (status == sf::Socket::Disconnected)
			return status;
		else if (status == sf::Socket::Error)
			return sf::Socket::Disconnected;
		total += wr;
	}
	return sf::Socket::Done;
}

void UdpConnect::sendPackets(sfs::Scene &scene) noexcept
{
	while (!_toWrite.empty())
	{
		auto &p = _toWrite.front();
		auto status = sendWrapper(_socket, p.getNativeHandle(), p.getSize());
		if (status == sf::Socket::Disconnected)
		{
			scene.clear();
			scene.addGameObject<cf::GameManager>();
			scene.addGameObject<cf::MenuManager>();
			scene.addGameObject<cf::InputHandler>();
			return;
		}
		_toWrite.pop();
	}
}

void UdpConnect::update(sfs::Scene &scene) noexcept
{
	while (_serializer.getSize() > sizeof(UdpPrctl))
	{
		UdpPrctl header;
		_serializer >>= header;
		if (header.isCorrect() == false)
		{
			_serializer.clear();
			return;
		}
		if (_serializer.getSize() < header.getLength() + sizeof(UdpPrctl))
			return;
		_serializer.shift(sizeof(UdpPrctl));
		executePacket(scene, header);
	}
	sendPackets(scene);
	receiveData(scene);
}
} // namespace cf
