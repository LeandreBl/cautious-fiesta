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
		_gameManager->_tcp->connect(_gameManager->_character.getName(), "192.168.0.9"); //TODO mettre la bonne ip et gérer le cas ou c'est mauvaise ip depuis le fail co de Connect
		_RSelector = &addChild<RoomSelector>(scene, std::ref(scene));
		_gameManager->_tcp->getRooms();
    }

	void roomScene::handleConnect(Serializer &toread) noexcept
	{
        uint8_t test = 0;
        toread.get(test); //TODO popUP
        std::cout << "login" << (int)test << std::endl;
    }

    void roomScene::handleDisconnect(Serializer &toread) noexcept
	{
        uint8_t test = 0;
        toread.get(test);
        std::cout << "logout" << (int)test << std::endl;
    }

    void roomScene::handleCreateRoom(Serializer &toread) noexcept
	{
        uint8_t test = 0;
        toread.get(test);
        std::cout << "create room" << (int)test << std::endl;
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
            std::cout << "il y a "<< nbPlayers << " joueurs dans la room: " << roomName << std::endl;
            _rooms.emplace_back(std::make_pair(nbPlayers, roomName));
        }
        _RSelector->drawRooms(_rooms);
    }

    void roomScene::handleJoinRoom(Serializer &toread) noexcept
    {
        uint8_t test = 0;
        toread.get(test);
        std::cout << "join room" << (int)test << std::endl;
    }

    void roomScene::handleLeaveRoom(Serializer &toread) noexcept
    {
        uint8_t test = 0;
        toread.get(test);
        std::cout << "leave room" << (int)test << std::endl;
    }

    void roomScene::deleteScene() noexcept
    {
        if (_RSelector->RoomListPos().x <= -1000) {
            _RSelector->destroyRoom();
            return;
        }
        Character character;
	    _gameManager->_character = character;
	    _gameManager->_ip = "";
		_gameManager->_tcp->disconnect();
    }
}