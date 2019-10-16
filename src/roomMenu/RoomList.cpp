#include "RoomList.hpp"

namespace cf 
{

    roomList::roomList(sfs::Scene &scene) noexcept 
        : _room(nullptr), _createRoom(nullptr), _box(nullptr), _imageCreationRoom(nullptr), _selectedRoom(nullptr), _gameManager(nullptr)
    {
        setPosition(sf::Vector2f(0, 30));
        auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
	    auto texture = scene.getAssetTexture("assets/sprites/Menu/ui/BlankButton2.png");
        _room = &addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(50, 0),
		                                std::bind(&roomList::drawButtonCreateRoom, this, std::ref(scene)),
		                                "create room", sf::Color::White, 25);
        _room->setScale(sf::Vector2f(1.5, 1.5));
        _room->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(50, 0));

        _selectedRoom = &addChild<Room>(scene);
        _gameManager = scene.getGameObjects<GameManager>()[0];
    }

    void roomList::addRoom(sfs::Scene &scene, const std::string &name, int mul, int players) noexcept 
    {
        auto pos = this->getPosition();
        pos.y += 132;
        this->setPosition(pos);
        auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
	    auto texture = scene.getAssetTexture("assets/sprites/Menu/ui/BlankButton2.png");
        auto &Button = _room->addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(50, 0),
		                                std::bind(&roomList::joinRoom, this, name),
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
        } else if (_box == nullptr) {
            auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
            auto texture = scene.getAssetTexture("assets/sprites/Menu/ui/BlankButton2.png");
            _imageCreationRoom = &addComponent<sfs::Sprite>(*texture, sf::Vector2f(605, 0));
            _imageCreationRoom->setScale(sf::Vector2f(0.75, 0.75));
            _createRoom = &addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(605, 50),
		                            std::bind(&roomList::createRoom, this),
		                            "create", sf::Color::White, 20);
            _createRoom->setScale(sf::Vector2f(0.75, 0.75));
            _createRoom->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(605, 50));
            _box = &addChild<sfs::InputBox>(scene, *font, sf::Vector2f(645, 10), "room's name", sf::Color::White, 25);
            _box->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(645, 10));
        }
    }

    void roomList::createRoom() noexcept
    {
        if (_box->string() != "") {
            _gameManager->_tcp->createRoom(_box->string());
            _box->destroy();
            _box = nullptr;
            _createRoom->destroy();
            _createRoom = nullptr;
            _imageCreationRoom->destroy();
            _imageCreationRoom = nullptr;
        }
    }

    void roomList::joinRoom(const std::string &name) noexcept
    {
        std::cout << name << std::endl;
        _gameManager->_tcp->joinRoom(name);
        _selectedRoom->setImage(name);
        setPosition(sf::Vector2f(-1000, getPosition().y));
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

    void roomList::HideRoom() noexcept
    {
        _selectedRoom->hideImage();
        setPosition(sf::Vector2f(0, getPosition().y));
        _gameManager->_tcp->leaveRoom();
    }
}