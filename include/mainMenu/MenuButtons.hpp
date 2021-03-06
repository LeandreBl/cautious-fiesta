#pragma once

#include "MenuUi.hpp"
#include "CharacterSelector.hpp"

namespace cf
{
class ExitButton : public sfs::GameObject
{
      public:
	ExitButton() noexcept {};
	void start(sfs::Scene &scene) noexcept;

      protected:
	void closeScene(sfs::Scene &scene) const noexcept
	{
		scene.close();
	};
};

class PlayButton : public sfs::GameObject
{
      public:
	PlayButton() noexcept : _box(nullptr), _CSelection(nullptr){};
	void start(sfs::Scene &scene) noexcept;

      protected:
	void play(sfs::Scene &scene) noexcept;
	IpInputBox *_box;
	CharacterSelector *_CSelection;
};
} // namespace cf
