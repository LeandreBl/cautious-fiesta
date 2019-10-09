#include "MenuManager.hpp"

namespace cf {

    MenuManager::MenuManager() noexcept
        : _mainMenu(nullptr), _scroller(nullptr), _gameManager(nullptr)
        {}
    
    void MenuManager::start(sfs::Scene &scene) noexcept
    {
        _gameManager = scene.getGameObjects<GameManager>()[0];
        _scroller = &addChild<Scroller>(scene);
        auto sound = scene.getAssetSoundBuffer("assets/musics/menuMusic.ogg");
	    addComponent<sfs::Sound>(*sound, true, true);
        _mainMenu = &addChild<MainMenu>(scene, _scroller);
    }

    void MenuManager::update(sfs::Scene &) noexcept
    {
        if (_gameManager->_character.getName() != "noName" && _gameManager->_ip != "") {
            std::cout << "J'ai mon player" << std::endl;
        }
    }
}