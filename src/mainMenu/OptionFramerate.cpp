#include "Option.hpp"
#include "PaddedSprite.hpp"

namespace cf
{

    optionFrameRate::optionFrameRate() noexcept
	    : _frameRateText(nullptr), _decreaseFrameRate(nullptr),
	      _augmentFrameRate(nullptr)
    {
    };

    void optionFrameRate::start(sfs::Scene &scene) noexcept
	{
		_frameRateText = &addComponent<sfs::Text>(
			*scene.getAssetFont(
				"local-assets/fonts/commodore-64.ttf"),
			"FRAME RATE", sf::Color::White, 30);
		_decreaseFrameRate = &addChild<sfs::Button>(
			scene,
			*scene.getAssetTexture(
				"local-assets/sprites/Menu/ui/ArrowButton.png"),
			*scene.getAssetFont(
				"local-assets/fonts/commodore-64.ttf"),
			sf::Vector2f(-1000, -1000),
			std::bind(&optionFrameRate::lowerFrame, this,
				  std::ref(scene)));
		_decreaseFrameRate->setScale(sf::Vector2f(1.5, 1.5));
		_decreaseFrameRate->addComponent<PadderH<sfs::Button>>(
			9, *_decreaseFrameRate);
		_decreaseFrameRate->addComponent<PadderW<sfs::Button>>(
			-45, *_decreaseFrameRate);

		_augmentFrameRate = &addChild<sfs::Button>(
			scene,
			*scene.getAssetTexture(
				"local-assets/sprites/Menu/ui/ArrowButton.png"),
			*scene.getAssetFont(
				"local-assets/fonts/commodore-64.ttf"),
			sf::Vector2f(-1000, -1000),
			std::bind(&optionFrameRate::augmentFrame, this,
				  std::ref(scene)));
		_augmentFrameRate->setScale(sf::Vector2f(1.5, 1.5));
		_augmentFrameRate->setRotate(180);
		_augmentFrameRate->addComponent<PadderH<sfs::Button>>(
			35, *_augmentFrameRate);
		_augmentFrameRate->addComponent<PadderW<sfs::Button>>(
			80, *_augmentFrameRate);

		framerate = scene.framerate();
		_frameNumber = &addComponent<sfs::Text>(
			*scene.getAssetFont(
				"local-assets/fonts/commodore-64.ttf"),
			std::to_string(framerate), sf::Color::White, 30,
			sf::Vector2f(85, 50));
	}

    void optionFrameRate::update(sfs::Scene &) noexcept
    {
        _frameNumber->setString(std::to_string(framerate));
    }

    void optionFrameRate::lowerFrame(sfs::Scene &scene) noexcept
    {
        if (framerate - 20 <= 40)
            framerate = 40;
        else
            framerate -= 20;
        scene.framerate(framerate);
    }

    void optionFrameRate::augmentFrame(sfs::Scene &scene) noexcept
    {
        if (framerate + 20 >= 200)
            framerate = 200;
        else
            framerate += 20;
        scene.framerate(framerate);
    }
}