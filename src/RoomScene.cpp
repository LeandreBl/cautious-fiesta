#include "RoomScene.hpp"
#include "GameManager.hpp"

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
		_RSelector = &addChild<RoomSelector>(scene);
    }

    void roomScene::deleteScene() noexcept
    {
        Character character;
	    _gameManager->_character = character;
	    _gameManager->_ip = "";
		_gameManager->_tcp->disconnect();
    }
}