#include "RoomSelection.hpp"
#include "GameManager.hpp"

namespace cf 
{
    void rooms::drawGameroom(sfs::Scene &scene) noexcept 
    {
        if (_name == "create room" && _box != nullptr) {
            _box->destroy();
            _box = nullptr;
            _createRoom->destroy();
            _createRoom = nullptr;
            _imageCreationRoom->destroy();
            _imageCreationRoom = nullptr;
        } else if (_name == "create room" && _box == nullptr) {
            auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
            auto texture = scene.getAssetTexture("assets/sprites/Menu/ui/BlankButton2.png");
            _imageCreationRoom = &addComponent<sfs::Sprite>(*texture, sf::Vector2f(609, 0));
            _imageCreationRoom->setScale(sf::Vector2f(0.75, 0.75));
            _createRoom = &addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(609, 53),
		                            std::bind(&rooms::createRoom, this, std::ref(scene)),
		                            "create", sf::Color::White, 20);
            _createRoom->setScale(sf::Vector2f(0.75, 0.75));
            _box = &addChild<sfs::InputBox>(scene, *font, sf::Vector2f(645, 10), "room's name", sf::Color::White, 25);
        }
    }

    void rooms::createRoom(sfs::Scene &scene) noexcept
    {
        if (_box->string() != "") {
            auto gameManager = scene.getGameObjects<GameManager>()[0];
            gameManager->_tcp->createRoom(_box->string());
            _box->destroy();
            _box = nullptr;
            _createRoom->destroy();
            _createRoom = nullptr;
            _imageCreationRoom->destroy();
            _imageCreationRoom = nullptr;
        }
    }
}