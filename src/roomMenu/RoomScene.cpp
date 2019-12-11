#include <filesystem>
#include <Padder.hpp>
#include <Asset.hpp>
#include "RoomScene.hpp"
#include "MenuManager.hpp"
#include "Game.hpp"

namespace cf {

roomScene::roomScene(sfs::Scene &scene) noexcept
	: sfs::GameObject(sf::Vector2f(), "roomScene")
	, _scene(scene)
{
	auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	auto texture = scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton1.png");
	if (font == nullptr || texture == nullptr) {
		errorLog("[RoomScene] Quit button couldn't load the font or the texture");
		destroy();
		return;
	}
	_backToMenu = &addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(0, 0),
					     std::bind(&roomScene::deleteScene, this), "Back",
					     sf::Color::White, 25);
	_backToMenu->setScale(sf::Vector2f(1.2, 1.7));
	_backToMenu->addComponent<PadderR<sfs::Button>>(25.f, *_backToMenu);
	_backToMenu->addComponent<PadderB<sfs::Button>>(25.f, *_backToMenu);

	_roomList = &addChild<roomList>(scene, std::ref(scene));
}

void roomScene::start(sfs::Scene &scene) noexcept
{
	_gameManager = scene.getGameObjects<GameManager>()[0];
	_gameManager->_tcp->bind(scene);
	if (_gameManager->_tcp->connect(_gameManager->_character, _gameManager->_ip) == -84) {
		_gameManager->_popup->push("Connection fail, invalid IP");
		Character character;
		_gameManager->_character = character;
		_gameManager->_ip = "";
		ConnectionError = true;
	}
}

void roomScene::update(sfs::Scene &) noexcept
{
	if (ConnectionError == true) {
		auto v2 = _scene.getGameObjects<MenuManager>();
		if (!v2.empty()) {
			v2[0]->addChild<MainMenu>(_scene, v2[0]->getScroller());
		}
		destroy();
	}
	if (_checkAssets == true && _assetsPath.empty() == true) {
		_gameManager->_tcp->AssetRequirementIsDone();
		_checkAssets = false;
	}
}

void roomScene::handleConnect(Serializer &s) noexcept
{
	bool isOk = 0;
	s >> isOk;
	if (isOk == false) {
		_gameManager->_popup->push("Connection fail, Player already exist");
		Character character;
		_gameManager->_character = character;
		_gameManager->_ip = "";
		return;
	}
	_gameManager->_tcp->getRooms();
}

void roomScene::handleDisconnect(Serializer &s) noexcept
{
	bool isOk = 0;
	s >> isOk;
	if (isOk) {
		Character character;
		_gameManager->_character = character;
		_gameManager->_ip = "";
		auto v2 = _scene.getGameObjects<MenuManager>();
		if (!v2.empty()) {
			v2[0]->addChild<MainMenu>(_scene, v2[0]->getScroller());
		}
		destroy();
	}
}

void roomScene::handleGameStart(Serializer &s) noexcept
{
	uint16_t port;

	s >> port;
	if (_gameManager->_udp == nullptr)
		_gameManager->_udp = &_gameManager->addChild<UdpConnect>(_scene, *_gameManager);
	int status = _gameManager->_udp->connect(port, _gameManager->_ip);
	//if (status == -1) {
	//	_gameManager->destroy();
	//	return;
	//}
	_gameManager->_gameStarted = true;
	auto v = _scene.getGameObjects<MenuManager>();
	if (!v.empty()) {
		_scene.addGameObject<Game>(_scene);
		v[0]->destroy();
	}
}

void roomScene::handleAssetRequirement(Serializer &s) noexcept
{
	uint64_t size;
	s >> size;
	std::string fileName;
	uint64_t fileSize;
	uint64_t checkSum;
	for (uint64_t i = 0; i != size; i += 1) {
		s >> fileName;
		s >> fileSize;
		s >> checkSum;
		if (std::filesystem::exists("assets") == false)
			std::filesystem::create_directory("assets");
		if (std::filesystem::exists("assets/SpriteSheets") == false)
			std::filesystem::create_directory("assets/SpriteSheets");
		if (std::filesystem::exists(fileName) == false
		    || std::filesystem::file_size(fileName) != fileSize
		    || common::computeChksum(fileName) != checkSum) {
			if (std::filesystem::exists(fileName) == true)
				std::filesystem::remove(fileName);
			_assetsPath.push_back(fileName);
			_gameManager->_tcp->loadAsset(fileName);
		}
	}
	_checkAssets = true;
}

void roomScene::handleLoadAsset(Serializer &s) noexcept
{
	uint16_t tcpPort;
	uint64_t fileSize;
	std::string fileName;
	uint64_t checkSum;
	s >> tcpPort;
	s >> fileSize;
	s >> fileName;
	s >> checkSum;
	addChild<assetLoader>(_scene, std::ref(_scene), fileName, tcpPort, _gameManager->_ip,
			      fileSize, checkSum, std::ref(_assetsPath));
}

void roomScene::deleteScene() noexcept
{
	if (_roomList->getPosition().x <= -1000) {
		_gameManager->_tcp->leaveRoom();
		return;
	}
	_gameManager->_tcp->disconnect();
}
} // namespace cf