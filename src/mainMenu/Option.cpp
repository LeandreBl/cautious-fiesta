#include "MainMenu.hpp"

namespace cf
{
    void optionBackground::start(sfs::Scene &scene) noexcept 
    {
        srand(time(nullptr));
        setPosition(sf::Vector2f(0, 1400));
        int choice = std::rand() % 2;
        if (choice == 0)
            _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/OptionBackground.png"));
        else if (choice == 1)
            _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/Metro.png"));
        _velo = &addComponent<sfs::Velocity>(sf::Vector2f(0, -650));
    }
    void optionBackground::update(sfs::Scene &) noexcept
    {
        if (_velo != nullptr) {
            auto pos = getPosition();
            if (pos.y <= 0) {
                pos.y = 0;
                _velo->destroy();
                _velo = nullptr;
            }
        }
    }
    sf::FloatRect optionBackground::getGlobalBounds() noexcept 
	{
		return _image->getGlobalBounds();
	}

    void optionSound::lowerSound(sfs::Scene &scene) noexcept 
    {
        float volume = scene.getGameObjects<MainMenu>()[0]->getComponents<sfs::Sound>()[0]->getVolume();
        if (volume <= 10)
            volume = 0;
        else
            volume -= 10;
        scene.getGameObjects<MainMenu>()[0]->getComponents<sfs::Sound>()[0]->setVolume(volume); //TODO GAME MANAGER qui contient son
    }

    void optionSound::augmentSound(sfs::Scene &scene) noexcept
    {
        float volume = scene.getGameObjects<MainMenu>()[0]->getComponents<sfs::Sound>()[0]->getVolume();
        if (volume >= 100)
            volume = 100;
        else
            volume += 10;
        scene.getGameObjects<MainMenu>()[0]->getComponents<sfs::Sound>()[0]->setVolume(volume); //TODO GAME MANAGER qui contient son
    }
}