#include "Game.hpp"

namespace cf
{
    void Game::start(sfs::Scene &scene) noexcept
    {
        scene.subscribe(*this, sf::Event::Closed);
        scene.subscribe(*this, sf::Event::KeyPressed);
        _soundManager = &addChild<SoundManager>(scene);
    }

    void Game::quitGame(sfs::Scene &scene, bool quit) noexcept
    {
        //TODO SAUVGARDE DU PERSO QUI A EVOLUE DANS LE CONG.DAT
        if (quit == false) {
		    scene.close();
        } else {
            //TODO REVENIR AU MENU
        }
    }

    void Game::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
    {
	    if (event.type == sf::Event::Closed)
            quitGame(scene, false);
        if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Escape)
            {
                if (scene.getGameObjects<optionScene>().empty() == true)
                    _options = &addChild<optionScene>(scene); // TODO bouton return to menu (send close room and disconnect) && faire bouton quit game qui appelle quitGame
                else {
                    _options->destroy();
                    _options = nullptr;
                }
            }
    }
}