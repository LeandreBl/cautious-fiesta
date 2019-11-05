#include "Option.hpp"
#include "PaddedSprite.hpp"
#include "SoundManager.hpp"

namespace cf
{

    optionSound::optionSound() noexcept
	    : _soundText(nullptr), _decreaseSound(nullptr),
	      _augmentSound(nullptr), _soundBar(nullptr)
    {
    };

    void optionSound::start(sfs::Scene &scene) noexcept
	{
		_soundText = &addComponent<sfs::Text>(
			*scene.getAssetFont(
				"local-assets/fonts/commodore-64.ttf"),
			"SOUND", sf::Color::White, 30);
		_decreaseSound = &addChild<sfs::Button>(
			scene,
			*scene.getAssetTexture(
				"local-assets/sprites/Menu/ui/ArrowButton.png"),
			*scene.getAssetFont(
				"local-assets/fonts/commodore-64.ttf"),
			sf::Vector2f(-100, -100),
			std::bind(&optionSound::lowerSound, this,
				  std::ref(scene)));
		_decreaseSound->setScale(sf::Vector2f(1.5, 1.5));
		_decreaseSound->addComponent<PadderH<sfs::Button>>(
			-96, *_decreaseSound);
		_decreaseSound->addComponent<PadderW<sfs::Button>>(
			-86, *_decreaseSound);

		_augmentSound = &addChild<sfs::Button>(
			scene,
			*scene.getAssetTexture(
				"local-assets/sprites/Menu/ui/ArrowButton.png"),
			*scene.getAssetFont(
				"local-assets/fonts/commodore-64.ttf"),
			sf::Vector2f(-1000, -1000),
			std::bind(&optionSound::augmentSound, this,
				  std::ref(scene)));
		_augmentSound->setScale(sf::Vector2f(1.5, 1.5));
		_augmentSound->setRotate(180);
		_augmentSound->addComponent<PadderH<sfs::Button>>(
			-69, *_augmentSound);
		_augmentSound->addComponent<PadderW<sfs::Button>>(
			115, *_augmentSound);

		float volume = 0;
		auto sound = scene.getGameObjects<SoundManager>()[0]->getComponents<sfs::Sound>();
		if (sound.empty() == true)
			volume = 100;
		else
			volume = sound[0]->getVolume();

		_soundBar = &addComponent<sfs::Rectangle>(
			sf::Vector2f(-16, 50),
			sf::Vector2f((150 * volume) / 100, 30),
			sf::Color::White);
	}

     void optionSound::lowerSound(sfs::Scene &scene) noexcept 
    {
        float volume = scene.getGameObjects<SoundManager>()[0]->getComponents<sfs::Sound>()[0]->getVolume();
        if (volume <= 10) {
            volume = 0;
            _soundBar->setSize(sf::Vector2f(0, 30));
        } else {
            volume -= 10;
            auto size = _soundBar->getSize();
            size.x = (150 * volume) / 100;
            _soundBar->setSize(size);
        }
        scene.getGameObjects<SoundManager>()[0]->getComponents<sfs::Sound>()[0]->setVolume(volume);
    }

    void optionSound::augmentSound(sfs::Scene &scene) noexcept
    {
        float volume = scene.getGameObjects<SoundManager>()[0]->getComponents<sfs::Sound>()[0]->getVolume();
        if (volume >= 95) {
            volume = 100;
            _soundBar->setSize(sf::Vector2f(150, 30));
        } else {
            volume += 10;
            auto size = _soundBar->getSize();
            size.x = (150 * volume) / 100;
            _soundBar->setSize(size);
        }
        scene.getGameObjects<SoundManager>()[0]->getComponents<sfs::Sound>()[0]->setVolume(volume);
    }
}