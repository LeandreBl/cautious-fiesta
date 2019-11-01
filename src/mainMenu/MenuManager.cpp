#include "MenuManager.hpp"

namespace cf {

    MenuManager::MenuManager() noexcept
        : _mainMenu(nullptr), _scroller(nullptr), _gameManager(nullptr), _soundManager(nullptr), _roomScene(nullptr)
        {}

    void MenuManager::start(sfs::Scene &scene) noexcept
    {
	    scene.subscribe(*this, sf::Event::Closed);
        _gameManager = scene.getGameObjects<GameManager>()[0];
        _scroller = &addChild<Scroller>(scene);
        _soundManager = &addChild<SoundManager>(scene);
        _soundManager->addSound(scene, "local-assets/musics/menuMusic.ogg");
        _mainMenu = &addChild<MainMenu>(scene, _scroller);
    }

    void MenuManager::update(sfs::Scene &scene) noexcept
    {
        if (_gameManager->_character.getName() != "noName" && _gameManager->_ip != "" && _mainMenu != nullptr) {
            _mainMenu->destroy();
            _mainMenu = nullptr;
            _roomScene = &addChild<roomScene>(scene, std::ref(scene));
        }
        if (_gameManager->_character.getName() == "noName" && _gameManager->_ip == "" && _roomScene != nullptr) {
            _roomScene->destroy();
            _roomScene = nullptr;
            _mainMenu = &addChild<MainMenu>(scene, _scroller);
        }
        if (_gameManager->_gameStarted == true) {
            _gameManager->_tcp->bindAfterGameStarted(std::ref(scene));
            _gameManager->_game = &scene.addGameObject<Game>();
            this->destroy();
        }
    }

    void MenuManager::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
    {
	    if (event.type == sf::Event::Closed) {
		    scene.close();
        }
    }
}