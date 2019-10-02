#pragma once

#include <SFML/Audio.hpp>
#include <IComponent.hpp>

namespace cf
{
  class Sound : public sfs::IComponent, public sf::Sound
  {
  public:
    Sound(const sf::SoundBuffer &soundBuf, bool loop = false, bool autoPlay = false)  noexcept
      : sf::Sound(soundBuf)
    {
      setLoop(loop);
      if (autoPlay == true)
	play();
    }
  protected:
  };
}
