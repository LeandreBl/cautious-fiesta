#include "RoomScene.hpp"
#include "PaddedSprite.hpp"

namespace cf
{
    void roomScene::start(sfs::Scene &scene) noexcept 
    {
        auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
	    auto texture = scene.getAssetTexture("assets/sprites/Menu/ui/BlankButton1.png");
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

		_gameManager = scene.getGameObjects<GameManager>()[0];
		_gameManager->_tcp->bind(scene);
		if (_gameManager->_tcp->connect(_gameManager->_character, _gameManager->_ip) == -84) {
            _gameManager->_popup->push("Connection fail, invalid IP");
            Character character;
	        _gameManager->_character = character;
	        _gameManager->_ip = "";
        }
		_RSelector = &addChild<RoomSelector>(scene, std::ref(scene));
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
    }

    void roomScene::handleCreateRoom(Serializer &toread) noexcept
	{
        uint8_t isOk = 0;
        toread.get(isOk);
        if ((int)isOk == 0)
            _gameManager->_popup->push("The gameroom already exist");
    }

    void roomScene::handleDeleteRoom(Serializer &toread) noexcept
    {
        uint8_t isOk = 0;
        toread.get(isOk);
    }

	void roomScene::handleRoomList(Serializer &toread) noexcept
	{
        uint64_t size = 0;
        uint64_t nbPlayers;
        std::string roomName;
        toread.get(size);
        std::vector<std::pair<uint64_t, std::string>> _rooms;
        for (uint64_t i = 0; i != size; i += 1) {
            toread.get(nbPlayers);
            toread.get(roomName);
            _rooms.emplace_back(std::make_pair(nbPlayers, roomName));
        }
        _RSelector->drawRooms(_rooms);
    }

    void roomScene::handleJoinRoom(Serializer &toread) noexcept // TODO GESTION ERREUR
    {
        uint8_t isOk = 0;
        toread.get(isOk);
    }

    void roomScene::handleLeaveRoom(Serializer &toread) noexcept
    {
        uint8_t isLeaving = 0;
        toread.get(isLeaving);
        if ((int)isLeaving == 1)
            _RSelector->destroyRoom();
    }

    void roomScene::handlePlayerList(Serializer &toread) noexcept
    {
        uint8_t isOk = 0;
        toread.get(isOk);
        if ((int)isOk == 0) {
            _gameManager->_popup->push("No player list");
            return ;
        }
        std::string roomName;
        toread.get(roomName);
        uint64_t size;
        toread.get(size);
        std::string name;
        std::vector<std::pair<uint64_t, std::string>> players;
        for (uint64_t i = 0; i != size; i+= 1) {
            toread.get(isOk);
            toread.get(name);
            players.emplace_back(std::make_pair(isOk, name));
        }
        _RSelector->updatePlayerInRoom(players);
    }

    void roomScene::handleToggleReadyState(Serializer &toread) noexcept
    {
        uint8_t state = 0;
        toread.get(state);
        std::vector<std::pair<uint64_t, std::string>> players;
        _RSelector->updatePlayerInRoom(players, state);
    }

    void roomScene::handleGameStart(Serializer &toread) noexcept
	{
        uint16_t port = 0;
        toread.get(port);
        _gameManager->_udp->setPort(port);
        _gameManager->_gameStarted = true;
    }

    void roomScene::handleSendMessage(Serializer &toread) noexcept
    {
        uint8_t isOk = 0;
        toread.get(isOk);
    }

    void roomScene::handleReceiveMessage(Serializer &toread) noexcept
    {
        std::string name;
        toread.get(name);
        std::string message;
        toread.get(message);
        auto chat = _scene.getGameObjects<Chat>()[0];
        chat->receiveMessage(name + " : " + message);
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
            if (std::filesystem::exists(fileName) == true) {
                if (std::filesystem::file_size(fileName) == fileSize && easyCheckSum(fileName) == checkSum)
                    std::cout << "exist and correct" << std::endl;
                else {
                    std::filesystem::remove(fileName);
                    std::cout << "exist but invalid" << std::endl;
                    _assetsPath.push_back(fileName);
                    _gameManager->_tcp->loadAsset(fileName);
                }
            } else {
                std::cout << "doesn't exist" << std::endl;
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
        if (_RSelector->RoomListPos().x <= -1000) {
            _gameManager->_tcp->leaveRoom();
            return;
        }
        Character character;
	    _gameManager->_character = character;
	    _gameManager->_ip = "";
		_gameManager->_tcp->disconnect();
    }

    uint64_t easyCheckSum(const std::string &filename) noexcept
    {
 	    std::ifstream file;
	    char buffer[4096];
	    uint64_t chk = 0;

	    file.open(filename);
	    if (!file.is_open())
	        return 0;
	    std::streamsize rd;
	    do {
	        rd = file.readsome(buffer, sizeof(buffer));
	        for (std::streamsize i = 0; i < rd; ++i)
	                chk += ~buffer[i] & 0xF0F0F0F0F;
	    } while (rd == sizeof(buffer));
	    return chk;
    }
}