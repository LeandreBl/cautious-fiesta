#include <Sound.hpp>
#include "MainMenu.hpp"

namespace cf
{
    void Background::start(sfs::Scene &scene) noexcept 
    {
        if (_path == "") {
            srand(time(nullptr));
            setPosition(sf::Vector2f(0, 1400));
            int choice = std::rand() % 2;
            if (choice == 0)
                _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/OptionBackground.png"));
            else if (choice == 1)
                _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/Metro.png"));
        }
        _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture(_path));
    }
    void Background::update(sfs::Scene &) noexcept
    {
        if (_velo != nullptr && _lock == false) {
            auto pos = getPosition();
            if (pos.y <= 0) {
                pos.y = 0;
                _velo->destroy();
                _velo = nullptr;
                _lock = true;
            }
        }
    }
    sf::FloatRect Background::getGlobalBounds() noexcept 
	{
		return _image->getGlobalBounds();
	}

    void optionSound::lowerSound(sfs::Scene &scene) noexcept 
    {
        float volume = scene.getGameObjects<MainMenu>()[0]->getComponents<sfs::Sound>()[0]->getVolume();
        if (volume <= 10) {
            volume = 0;
            _soundBar->setSize(sf::Vector2f(0, 30));
        } else {
            volume -= 10;
            auto size = _soundBar->getSize();
            size.x = (150 * volume) / 100;
            _soundBar->setSize(size);
        }
        scene.getGameObjects<MainMenu>()[0]->getComponents<sfs::Sound>()[0]->setVolume(volume); //TODO GAME MANAGER qui contient son
    }

    void optionSound::augmentSound(sfs::Scene &scene) noexcept
    {
        float volume = scene.getGameObjects<MainMenu>()[0]->getComponents<sfs::Sound>()[0]->getVolume();
        if (volume >= 95) {
            volume = 100;
            _soundBar->setSize(sf::Vector2f(150, 30));
        } else {
            volume += 10;
            auto size = _soundBar->getSize();
            size.x = (150 * volume) / 100;
            _soundBar->setSize(size);
        }
        scene.getGameObjects<MainMenu>()[0]->getComponents<sfs::Sound>()[0]->setVolume(volume); //TODO GAME MANAGER qui contient son
    }
}