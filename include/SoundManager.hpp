#pragma once

#include <Sound.hpp>

namespace cf {
class SoundManager : public sfs::GameObject {
      public:
	void addSound(sfs::Scene &scene, std::string path)
	{
		auto sound = scene.getAssetSoundBuffer(path);
		addComponent<sfs::Sound>(*sound, true, true);
		// toremove
		getComponents<sfs::Sound>()[0]->setVolume(0);
	}
};
} // namespace cf