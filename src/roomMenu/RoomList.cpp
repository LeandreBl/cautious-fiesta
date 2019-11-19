#include <Offset.hpp>
#include "RoomList.hpp"

namespace cf {

roomList::roomList(sfs::Scene &scene) noexcept
	: _room(nullptr)
	, _createRoom(nullptr)
	, _box(nullptr)
	, _imageCreationRoom(nullptr)
	, _selectedRoom(nullptr)
	, _gameManager(nullptr)
	, _scene(scene)
	, _scrollbar(nullptr)
	, _lockScrollbar(0)
{
	setPosition(sf::Vector2f(0, 30));
	_gameManager = scene.getGameObjects<GameManager>()[0];
	auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	auto texture = scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png");
	_room = &addChild<sfs::Button>(
		scene, *texture, *font, sf::Vector2f(50, 0),
		std::bind(&roomList::drawButtonCreateRoom, this, std::ref(scene)), "create room",
		sf::Color::White, 25);
	_room->setScale(sf::Vector2f(1.5, 1.5));
	_room->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(50, 0));

	_deleteRoom = &addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(-1000, -1000),
					     std::bind(&TcpConnect::deleteRoom, _gameManager->_tcp),
					     "delete room", sf::Color::White, 20);
	_deleteRoom->setScale(sf::Vector2f(0.7, 0.7));

	_selectedRoom = &addChild<Room>(scene);
}

void roomList::createRoom() noexcept
{
	_gameManager->_tcp->createRoom(_box->string());
}

void roomList::addRoom(sfs::Scene &scene, const std::string &name, int mul, int players) noexcept
{
	auto pos = this->getPosition();
	pos.y += 132;
	this->setPosition(pos);
	auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	auto texture = scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png");
	auto &Button = _room->addChild<sfs::Button>(
		scene, *texture, *font, sf::Vector2f(50, 0),
		std::bind(&TcpConnect::joinRoom, _gameManager->_tcp, name),
		name + " " + std::to_string(players) + " players", sf::Color::White, 25);
	Button.setScale(sf::Vector2f(1.5, 1.5));
	Button.addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(50, -132 * mul));
}

void roomList::drawButtonCreateRoom(sfs::Scene &scene) noexcept
{
	if (_box != nullptr) {
		_box->destroy();
		_box = nullptr;
		_createRoom->destroy();
		_createRoom = nullptr;
		_imageCreationRoom->destroy();
		_imageCreationRoom = nullptr;
	}
	else if (_box == nullptr) {
		auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
		auto texture =
			scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png");
		_imageCreationRoom = &addComponent<sfs::Sprite>(*texture, sf::Vector2f(605, 0));
		_imageCreationRoom->setScale(sf::Vector2f(0.75, 0.75));
		_box = &addChild<sfs::InputBox>(scene, *font, sf::Vector2f(645, 10), "room's name",
						sf::Color::White, 25);
		_box->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(645, 10));
		_box->toggle(true);
		_createRoom = &addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(605, 50),
						     std::bind(&roomList::createRoom, this),
						     "create", sf::Color::White, 20);
		_createRoom->setScale(sf::Vector2f(0.75, 0.75));
		_createRoom->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(605, 50));
	}
}

void roomList::destroyRooms() noexcept
{
	auto pos = this->getPosition();
	auto rooms = _room->getChilds();
	for (auto &i : rooms) {
		i->destroy();
		pos.y -= 130;
	}
	this->setPosition(pos);
}

float roomList::getHeight() noexcept
{
	auto size = _room->getChilds();
	float height = 0;
	for (auto &i : size)
		height += static_cast<sfs::Button *>(i)->getGlobalBounds().height + 32;
	return height;
}

void roomList::update(sfs::Scene &) noexcept
{
	if (_selectedRoom->getRoomOwner() == _gameManager->_character.getName()) {
		auto pos = (_selectedRoom->getImageWidth() / 2)
			   - (_deleteRoom->getGlobalBounds().width / 2);
		_deleteRoom->setPosition(sf::Vector2f(pos, 1012));
	}
	if (_scrollbar != nullptr)
		if (_lockScrollbar != _scrollbar->getValue()) {
			float pos = (getHeight() - 950) * _scrollbar->getValue();
			setPosition(sf::Vector2f(0, getHeight() - pos));
			_lockScrollbar = _scrollbar->getValue();
		}
}

void roomList::handleJoinRoom(Serializer &toread) noexcept
{
	uint8_t isOk = 0;
	toread.get(isOk);
	if ((int)isOk == 1) {
		_selectedRoom->setImage();
		setPosition(sf::Vector2f(-1000, getPosition().y));
	}
}

void roomList::handleLeaveRoom(Serializer &toread) noexcept
{
	uint8_t isLeaving = 0;
	toread.get(isLeaving);
	if ((int)isLeaving == 1) {
		_selectedRoom->hideImage();
		setPosition(sf::Vector2f(0, getPosition().y));
		_deleteRoom->setPosition(sf::Vector2f(-1000, -1000));
	}
}

void roomList::handleCreateRoom(Serializer &toread) noexcept
{
	uint8_t isOk = 0;
	toread.get(isOk);
	if ((int)isOk == 0) {
		_gameManager->_popup->push("The gameroom already exist");
		_box->string("");
		_box->toggle(false);
	}
	else {
		_box->destroy();
		_box = nullptr;
		_createRoom->destroy();
		_createRoom = nullptr;
		_imageCreationRoom->destroy();
		_imageCreationRoom = nullptr;
	}
}

void roomList::handleDeleteRoom(Serializer &toread) noexcept
{
	uint8_t isOk = 0;
	toread.get(isOk);
}

void roomList::handleRoomList(Serializer &toread) noexcept
{
	uint64_t size = 0;
	uint64_t nbPlayers;
	std::string roomName;
	toread.get(size);
	destroyRooms();
	for (uint64_t i = 0; i != size; i += 1) {
		toread.get(nbPlayers);
		toread.get(roomName);
		addRoom(_scene, roomName, i + 1, nbPlayers);
		if (getPosition().y >= 950 && getPosition().x == 0 && _scrollbar == nullptr)
			_scrollbar = &addChild<sfs::Vnavbar>(_scene, sf::Vector2f(0, 0),
							     sf::Vector2f(30, 1080));
		else if (getPosition().y < 950 && _scrollbar != nullptr) {
			_scrollbar->destroy();
			_scrollbar = nullptr;
		}
	}
}
} // namespace cf