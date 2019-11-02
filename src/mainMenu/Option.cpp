#include "Option.hpp"
#include "GameManager.hpp"

namespace cf
{
    optionScene::optionScene() noexcept
	    : _menuBoxName(nullptr), _optionMenuBox(nullptr), _sound(nullptr),
	      _frameRate(nullptr)
    {
    };

    void optionScene::start(sfs::Scene &scene) noexcept
	{
		_optionMenuBox = &addChild<Background>(
			scene, "local-assets/sprites/Menu/ui/OptionWindow.png");
		_optionMenuBox->addComponent<PadderW<Background>>(
			0, *_optionMenuBox);
		_optionMenuBox->addComponent<PadderH<Background>>(
			0, *_optionMenuBox);

		_menuBoxName = &addChild<Text>(
			scene,
			*scene.getAssetFont(
				"local-assets/fonts/commodore-64.ttf"),
			"OPTIONS", sf::Vector2f(-1000, -1000), 30);
		_menuBoxName->addComponent<PadderW<Text>>(0, *_menuBoxName);
		_menuBoxName->addComponent<PadderH<Text>>(-204, *_menuBoxName);

		_sound = &addChild<optionSound>(scene);
		_sound->addComponent<PadderW<optionSound>>(0, *_sound);
		_sound->addComponent<PadderH<optionSound>>(-150, *_sound);

		_frameRate = &addChild<optionFrameRate>(scene);
		_frameRate->addComponent<PadderW<optionFrameRate>>(0,
								   *_frameRate);
		_frameRate->addComponent<PadderH<optionFrameRate>>(-50,
								   *_frameRate);

		_resumeButton = &addChild<sfs::Button>(
			scene,
			*scene.getAssetTexture(
				"local-assets/sprites/Menu/ui/BlankButton2.png"),
			*scene.getAssetFont(
				"local-assets/fonts/commodore-64.ttf"),
			sf::Vector2f(-1000, -1000),
			std::bind(&optionScene::closeOptions, this), "resume",
			sf::Color::White, 20);
		_resumeButton->setScale(sf::Vector2f(0.7, 0.5));
		_resumeButton->addComponent<PadderW<sfs::Button>>(
			0, *_resumeButton);
		_resumeButton->addComponent<PadderH<sfs::Button>>(
			170, *_resumeButton);
	}

    void optionScene::ButtonsInGame(sfs::Scene &scene) noexcept
	{
		auto BackToMenu = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
												*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
												std::bind(&optionScene::quitGame, this, std::ref(scene), true), "back to menu", sf::Color::White, 20);
        BackToMenu->setScale(sf::Vector2f(0.7, 0.5));
		BackToMenu->addComponent<PadderW<sfs::Button>>(0, *BackToMenu);
		BackToMenu->addComponent<PadderH<sfs::Button>>(70, *BackToMenu);

        auto quitGame = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
												*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
												std::bind(&optionScene::quitGame, this, std::ref(scene), false), "quit game", sf::Color::White, 20);
        quitGame->setScale(sf::Vector2f(0.7, 0.5));
        quitGame->addComponent<PadderW<sfs::Button>>(0, *quitGame);
        quitGame->addComponent<PadderH<sfs::Button>>(120, *quitGame);
	}

    void optionScene::quitGame(sfs::Scene &scene, bool quit) noexcept
    {
        auto gameManager = scene.getGameObjects<GameManager>()[0];
        gameManager->_game->quitGame(scene, quit);
    }

}