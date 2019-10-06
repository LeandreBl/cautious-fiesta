#pragma once

#include <iostream>
#include <GameObject.hpp>
#include <WScene.hpp>
#include "Button.hpp"
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

class OptionsButton : public sfs::GameObject
{
      public:
	void start(sfs::Scene &scene) noexcept;

      protected:
	void optionScene() noexcept;
};

class PlayButton : public sfs::GameObject
{
      public:
	PlayButton() noexcept : _box(nullptr), _CSelection(nullptr){};
	void start(sfs::Scene &scene) noexcept;

      protected:
	void play() noexcept;
	IpInputBox *_box;
	CharacterSelector *_CSelection;
};
} // namespace cf
