#include "Option.hpp"

namespace cf
{
    
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