#include <filesystem>
#include <Padder.hpp>
#include <Asset.hpp>
#include "RoomScene.hpp"

namespace cf
{

    roomScene::roomScene(sfs::Scene &scene) noexcept
        : _scene(scene)
    {
        auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	    auto texture = scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton1.png");
	    if (font == nullptr || texture == nullptr) {
		    errorLog("[RoomScene] Quit button couldn't load the font or the texture");
		    destroy();
		    return;
	    }
	    _backToMenu = &addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(0, 0),
		                                    std::bind(&roomScene::deleteScene, this),
		                                    "Back", sf::Color::White, 25);
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
        }
    }

    void roomScene::update(sfs::Scene &) noexcept
    {
        if (_checkAssets == true && _assetsPath.empty() == true)
        {
            _gameManager->_tcp->AssetRequirementIsDone();
            _checkAssets = false;
        }
    }

	void roomScene::handleConnect(Serializer &toread) noexcept
	{
        uint8_t isOk = 0;
        toread.get(isOk);
        if ((int)isOk == 0) {
            _gameManager->_popup->push("Connection fail, Player already exist");
            Character character;
	        _gameManager->_character = character;
	        _gameManager->_ip = "";
            return ;
        }
        _gameManager->_tcp->getRooms();
    }

    void roomScene::handleDisconnect(Serializer &toread) noexcept
	{
        uint8_t isOk = 0;
        toread.get(isOk);
        if ((int)isOk == 1) {
            Character character;
            _gameManager->_character = character;
            _gameManager->_ip = "";
        }
    }

    void roomScene::handleGameStart(Serializer &toread) noexcept
	{
        uint16_t port = 0;
        toread.get(port);
        auto answer = _gameManager->_udp->setPort(port, _gameManager->_ip);
        if (answer != -1 || answer != -84) //TODO gestion erreur en cas de -84
            _gameManager->_tcp->sendLocalPort(answer);
        _gameManager->_gameStarted = true;
    }

    void roomScene::handleAssetRequirement(Serializer &toread) noexcept
    {
        uint64_t size;
        toread.get(size);
        std::string fileName;
        uint64_t fileSize;
        uint64_t checkSum;
        for (uint64_t i = 0; i != size; i += 1) {
            toread.get(fileName);
            toread.get(fileSize);
            toread.get(checkSum);
            if (std::filesystem::exists(fileName) == false || std::filesystem::file_size(fileName) != fileSize || common::computeChksum(fileName) != checkSum) {
                if (std::filesystem::exists(fileName) == true)
                    std::filesystem::remove(fileName);
                _assetsPath.push_back(fileName);
                _gameManager->_tcp->loadAsset(fileName);
            }
        }
        _checkAssets = true;
    }

    void roomScene::handleLoadAsset(Serializer &toread) noexcept
    {
        uint16_t tcpPort;
        uint64_t fileSize;
        std::string fileName;
        uint64_t checkSum;
        toread.get(tcpPort);
        toread.get(fileSize);
        toread.get(fileName);
        toread.get(checkSum);
        addChild<assetLoader>(_scene, std::ref(_scene), fileName, tcpPort, _gameManager->_ip, fileSize, checkSum, std::ref(_assetsPath));
    }

    void roomScene::deleteScene() noexcept
    {
        if (_roomList->getPosition().x <= -1000) {
            _gameManager->_tcp->leaveRoom();
            return;
        }
		_gameManager->_tcp->disconnect();
    }
}