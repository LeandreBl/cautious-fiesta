#include <Offset.hpp>
#include "Option.hpp"
#include "GameManager.hpp"
#include "Game.hpp"
#include <Padder.hpp>

namespace cf
{
    void optionScene::start(sfs::Scene &scene) noexcept
	{
		_optionMenuBox = &addChild<Background>(scene, "local-assets/sprites/Menu/ui/OptionWindow.png");
		_optionMenuBox->addComponent<PadderW<Background>>(0, *_optionMenuBox);
		_optionMenuBox->addComponent<PadderH<Background>>(0, *_optionMenuBox);

		_menuBoxName = &addChild<Text>(scene, *scene.getAssetFont("local-assets/fonts/commodore-64.ttf"),
										"OPTIONS", sf::Vector2f(-1000, -1000), 30);
		_menuBoxName->addComponent<PadderW<Text>>(0, *_menuBoxName);
		_menuBoxName->addComponent<PadderH<Text>>(-204, *_menuBoxName);

		OptionButtons(scene);
		scene.getGameObjects<InputHandler>()[0]->changeOption(true);
	}

	void optionScene::update(sfs::Scene &scene) noexcept
	{
		if (scene.getGameObjects<optionKeyboard>().empty() == true && _keyboardActive == true) {
			_keyboard->destroy();
			OptionButtons(scene);
			_keyboardActive = false;
		}
	}

	void optionScene::KeyboardScene(sfs::Scene &scene) noexcept
	{
		_sound->destroy();
		_frameRate->destroy();
		_resumeButton->destroy();
		_keyboardScene->destroy();
		if (_backToMenu != nullptr && _quitGame != nullptr) {
			_backToMenu->destroy();
			_quitGame->destroy();
		}
		_keyboardActive = true;
		_keyboard = &addChild<optionKeyboard>(scene);
	}

	void optionScene::OptionButtons(sfs::Scene &scene) noexcept
	{
		_sound = &addChild<optionSound>(scene);
		_sound->addComponent<PadderW<optionSound>>(0, *_sound);
		_sound->addComponent<PadderH<optionSound>>(-150, *_sound);

		_frameRate = &addChild<optionFrameRate>(scene);
		_frameRate->addComponent<PadderW<optionFrameRate>>(0, *_frameRate);
		_frameRate->addComponent<PadderH<optionFrameRate>>(-50, *_frameRate);

		_resumeButton = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
												*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
												std::bind(&optionScene::closeOptions, this, std::ref(scene)), "resume", sf::Color::White, 20);
		_resumeButton->setScale(sf::Vector2f(0.7, 0.5));
		_resumeButton->addComponent<PadderW<sfs::Button>>(0, *_resumeButton);
		_resumeButton->addComponent<PadderH<sfs::Button>>(245, *_resumeButton);

		_keyboardScene = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
												*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
												std::bind(&optionScene::KeyboardScene, this, std::ref(scene)), "change controls", sf::Color::White, 20);
		_keyboardScene->setScale(sf::Vector2f(0.7, 0.5));
		_keyboardScene->addComponent<PadderW<sfs::Button>>(0, *_keyboardScene);
		_keyboardScene->addComponent<PadderH<sfs::Button>>(70, *_keyboardScene);
	}

    void optionScene::ButtonsInGame(sfs::Scene &scene) noexcept
	{
		_backToMenu = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
												*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
												std::bind(&optionScene::quitGame, this, std::ref(scene), true), "back to menu", sf::Color::White, 20);
        _backToMenu->setScale(sf::Vector2f(0.7, 0.5));
		_backToMenu->addComponent<PadderW<sfs::Button>>(0, *_backToMenu);
		_backToMenu->addComponent<PadderH<sfs::Button>>(120, *_backToMenu);

        _quitGame = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
												*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
												std::bind(&optionScene::quitGame, this, std::ref(scene), false), "quit game", sf::Color::White, 20);
        _quitGame->setScale(sf::Vector2f(0.7, 0.5));
        _quitGame->addComponent<PadderW<sfs::Button>>(0, *_quitGame);
        _quitGame->addComponent<PadderH<sfs::Button>>(170, *_quitGame);
	}

    void optionScene::quitGame(sfs::Scene &scene, bool quit) noexcept
    {
        auto game = scene.getGameObjects<Game>()[0];
        game->quitGame(scene, quit);
    }

	void optionScene::closeOptions(sfs::Scene &scene) noexcept
	{
		scene.getGameObjects<InputHandler>()[0]->changeOption(false);
		this->destroy();
	}

}