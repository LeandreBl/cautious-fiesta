#include <Tcp.hpp>

#include "TcpConnection.hpp"
#include "RoomScene.hpp"

namespace cf {
void TcpConnect::bind(sfs::Scene &scene) noexcept
{
	auto rScene = scene.getGameObjects<roomScene>()[0];
	autoBind(TcpPrctl::Type::LOGIN, &roomScene::handleConnect, rScene);
	autoBind(TcpPrctl::Type::LOGOUT, &roomScene::handleDisconnect, rScene);
	autoBind(TcpPrctl::Type::GAME_STARTED, &roomScene::handleGameStart, rScene);
	autoBind(TcpPrctl::Type::ASSETS_REQUIREMENT, &roomScene::handleAssetRequirement, rScene);
	autoBind(TcpPrctl::Type::ASSETS_SEND, &roomScene::handleLoadAsset, rScene);

	auto chat = scene.getGameObjects<Chat>()[0];
	autoBind(TcpPrctl::Type::SEND_MESSAGE, &Chat::handleSendMessage, chat);
	autoBind(TcpPrctl::Type::RECEIVE_MESSAGE, &Chat::receiveMessage, chat);

	auto room = scene.getGameObjects<Room>()[0];
	autoBind(TcpPrctl::Type::GET_GAMEROOM_PLAYERS_LIST, &Room::handlePlayerList, room);
	autoBind(TcpPrctl::Type::TOGGLE_READY, &Room::handleTogglePlayerReadyState, room);

	auto roomL = scene.getGameObjects<roomList>()[0];
	autoBind(TcpPrctl::Type::JOIN_GAMEROOM, &roomList::handleJoinRoom, roomL);
	autoBind(TcpPrctl::Type::LEAVE_GAMEROOM, &roomList::handleLeaveRoom, roomL);
	autoBind(TcpPrctl::Type::CREATE_GAMEROOM, &roomList::handleCreateRoom, roomL);
	autoBind(TcpPrctl::Type::DELETE_GAMEROOM, &roomList::handleDeleteRoom, roomL);
	autoBind(TcpPrctl::Type::GET_GAMEROOMS_LIST, &roomList::handleRoomList, roomL);
}

void TcpConnect::bindAfterGameStarted(sfs::Scene &scene) noexcept
{
	auto _gameManager = scene.getGameObjects<GameManager>()[0];
	autoBind(TcpPrctl::Type::LEAVE_GAMEROOM, &GameManager::disconnectAndLeaveRoom,
		 _gameManager);
	autoBind(TcpPrctl::Type::LOGOUT, &GameManager::disconnectAndLeaveRoom, _gameManager);
	autoBind(TcpPrctl::Type::GET_GAMEROOMS_LIST, &GameManager::updateRooms, _gameManager);

	auto chat = scene.getGameObjects<Chat>()[1];
	autoBind(TcpPrctl::Type::SEND_MESSAGE, &Chat::handleSendMessage, chat);
	autoBind(TcpPrctl::Type::RECEIVE_MESSAGE, &Chat::receiveMessage, chat);
}

void TcpConnect::send(const Serializer &packet) noexcept
{
	std::size_t sent = 0;
	if (_socket.send(packet.getNativeHandle(), packet.getSize(), sent) != sf::Socket::Done) {
		auto manager = _scene.getGameObjects<GameManager>()[0];
		manager->_popup->push("Connection lost...");
		Character character;
		manager->_ip = "";
		manager->_character = character;
		_socket.disconnect();
		_status = _socket.Disconnected;
		lock = false;
		if (manager->_gameStarted == true)
			manager->_gameFinished = true;
		return;
	}
	if (sent != packet.getSize())
		std::cout << "data mal envoyée\n";
}

int TcpConnect::connect(Character charac, const std::string &ip) noexcept
{
	Serializer packet;
	if (lock == false) {
		_status = _socket.connect(ip, 2121);
		if (_status == sf::Socket::Error)
			return -84;
		_socket.setBlocking(false);
		lock = true;
	}
	packet << charac.getName();
	packet << charac.getStats();
	packet << charac.getColor();
	packet.setHeader(TcpPrctl::Type::LOGIN);
	send(packet);
	return 0;
}

void TcpConnect::disconnect() noexcept
{
	Serializer packet;
	packet.setHeader(TcpPrctl::Type::LOGOUT);
	send(packet);
}

void TcpConnect::createRoom(const std::string &roomName) noexcept
{
	if (roomName != "") {
		Serializer packet;
		packet << roomName;
		packet.setHeader(TcpPrctl::Type::CREATE_GAMEROOM);
		send(packet);
	}
}

void TcpConnect::deleteRoom() noexcept
{
	Serializer packet;
	packet.setHeader(TcpPrctl::Type::DELETE_GAMEROOM);
	send(packet);
}

void TcpConnect::getRooms() noexcept
{
	Serializer packet;
	packet.setHeader(TcpPrctl::Type::GET_GAMEROOMS_LIST);
	send(packet);
}

void TcpConnect::joinRoom(const std::string &roomName) noexcept
{
	Serializer packet;
	packet << roomName;
	packet.setHeader(TcpPrctl::Type::JOIN_GAMEROOM);
	send(packet);
}

void TcpConnect::leaveRoom() noexcept
{
	Serializer packet;
	packet.setHeader(TcpPrctl::Type::LEAVE_GAMEROOM);
	send(packet);
}

void TcpConnect::toggleReadyState() noexcept
{
	Serializer packet;
	packet.setHeader(TcpPrctl::Type::TOGGLE_READY);
	send(packet);
}

void TcpConnect::sendMessage(const std::string &message) noexcept
{
	Serializer packet;
	packet << message;
	packet.setHeader(TcpPrctl::Type::SEND_MESSAGE);
	send(packet);
}

void TcpConnect::loadAsset(const std::string &asset) noexcept
{
	Serializer packet;
	packet << asset;
	packet.setHeader(TcpPrctl::Type::ASSETS_SEND);
	send(packet);
}

void TcpConnect::AssetRequirementIsDone() noexcept
{
	Serializer packet;
	packet << true;
	packet.setHeader(TcpPrctl::Type::ASSETS_REQUIREMENT);
	send(packet);
}

void TcpConnect::sendLocalPort(uint16_t port) noexcept
{
	Serializer packet;
	packet << port;
	packet.setHeader(TcpPrctl::Type::GAME_STARTED);
	send(packet);
}

void TcpConnect::update(sfs::Scene &) noexcept
{
	char buffer[1024];
	std::size_t rd;
	do {
		if (_socket.receive(buffer, sizeof(buffer), rd) != sf::Socket::Done)
			return;
		else
			_serializer.nativeSet(buffer, rd);
	} while (rd == sizeof(buffer));
	TcpPrctl header;
	while (_serializer.getSize() >= sizeof(header)) {
		_serializer >> header;
		header.display();
		if (_serializer.getSize() >= header.getLength() && header.isCorrect() == true)
			_callbacks[header.getType()](_serializer);
		else {
			disconnect();
			return;
		}
	}
}
} // namespace cf