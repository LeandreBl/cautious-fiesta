#include "Game.hpp"
#include "GameManager.hpp"

namespace cf
{
    Game::Game(sfs::Scene &scene) noexcept
    {
        scene.subscribe(*this, sf::Event::Closed);
        scene.subscribe(*this, sf::Event::KeyPressed);
        _soundManager = &addChild<SoundManager>(scene);
        _ui = &addChild<GameUi>(scene, std::ref(scene));
    }

    void Game::start(sfs::Scene &scene) noexcept
    {
        auto gameManager = scene.getGameObjects<GameManager>()[0];
        gameManager->_tcp->bindAfterGameStarted(std::ref(scene));
    }

    void Game::quitGame(sfs::Scene &scene, bool quit) noexcept
    {
        //TODO SAUVGARDE DU PERSO QUI A EVOLUE DANS LE CONG.DAT
        if (quit == false) {
		    scene.close();
        } else {
            auto gameManager = scene.getGameObjects<GameManager>()[0];
            gameManager->_tcp->sendMessage("disconnected");
            gameManager->_tcp->leaveRoom();
        }
    }

    void Game::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
    {
	    if (event.type == sf::Event::Closed)
            quitGame(scene, false);
        if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Escape)
            {
                if (scene.getGameObjects<optionScene>().empty() == true) {
                    _options = &addChild<optionScene>(scene);
                    _options->ButtonsInGame(scene);
                }
                else {
                    _options->destroy();
                    _options = nullptr;
                }
            }
    }
}