#include "MenuManager.hpp"

namespace cf {

    MenuManager::MenuManager() noexcept
        : _mainMenu(nullptr), _scroller(nullptr), _gameManager(nullptr), _soundManager(nullptr)
        {}
    
    void MenuManager::start(sfs::Scene &scene) noexcept
    {
	    scene.subscribe(*this, sf::Event::Closed);
        _gameManager = scene.getGameObjects<GameManager>()[0];
        _scroller = &addChild<Scroller>(scene);
        _soundManager = &addChild<SoundManager>(scene);
        _soundManager->addSound(scene, "assets/musics/menuMusic.ogg");
        _mainMenu = &addChild<MainMenu>(scene, _scroller);
    }

    void MenuManager::update(sfs::Scene &) noexcept
    {
        if (_gameManager->_character.getName() != "noName" && _gameManager->_ip != "" && _mainMenu != nullptr) {
            std::cout << "J'ai mon player" << std::endl;
            _mainMenu->destroy();
            _mainMenu = nullptr;
        }
    }

    void MenuManager::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
    {
	    if (event.type == sf::Event::Closed)
		    scene.close();
    }
}