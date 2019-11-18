#pragma once

#include <BasicShape.hpp>
#include <Button.hpp>
#include "Utils.hpp"
#include "Udp.hpp"
#include "InputHandler.hpp"

namespace cf
{

class optionSound : public sfs::UI
{
      public:
	optionSound() noexcept;
	void start(sfs::Scene &scene) noexcept;
	void lowerSound(sfs::Scene &scene) noexcept;
	void augmentSound(sfs::Scene &scnene) noexcept;
	sf::FloatRect getGlobalBounds() noexcept {return _soundText->getGlobalBounds();}
      protected:
	sfs::Text *_soundText;
	sfs::Button *_decreaseSound;
	sfs::Button *_augmentSound;
	sfs::Rectangle *_soundBar;
};

class optionFrameRate : public sfs::UI
{
      public:
	optionFrameRate() noexcept;
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;
	void lowerFrame(sfs::Scene &scene) noexcept;
	void augmentFrame(sfs::Scene &scene) noexcept;
	sf::FloatRect getGlobalBounds() noexcept {return _frameRateText->getGlobalBounds();}
      protected:
	sfs::Text *_frameRateText;
	sfs::Button *_decreaseFrameRate;
	sfs::Button *_augmentFrameRate;
	sfs::Text *_frameNumber;
	uint32_t framerate = 120;
};

class optionKeyboard : public sfs::UI
{
	public:
		void start(sfs::Scene &scene) noexcept;
		void update(sfs::Scene &scene) noexcept;
		sf::FloatRect getGlobalBounds() {return _optionMenuBox->getGlobalBounds();};
		void changeBinding(UdpPrctl::inputType type) noexcept;
		void setDefaultBindings() noexcept;
		void closeOptions() noexcept {this->destroy();};
	protected:
		sfs::Sprite *_optionMenuBox;
		std::vector<std::pair<sfs::Button *, sfs::Text *>> _buttons;
		InputHandler *_input;
};

class optionScene : public sfs::UI
{
      public:
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;
	void ButtonsInGame(sfs::Scene &scene) noexcept;
	void OptionButtons(sfs::Scene &scene) noexcept;
	void quitGame(sfs::Scene &scene, bool quit) noexcept;
	void closeOptions(sfs::Scene &scene) noexcept;
	void KeyboardScene(sfs::Scene &scene) noexcept;
      protected:
	Text *_menuBoxName = nullptr;
	Background *_optionMenuBox = nullptr;
	optionSound *_sound = nullptr;
	optionFrameRate *_frameRate = nullptr;
	optionKeyboard *_keyboard = nullptr;
	sfs::Button *_keyboardScene = nullptr;
	sfs::Button *_resumeButton = nullptr;
	sfs::Button *_backToMenu = nullptr;
	sfs::Button *_quitGame = nullptr;
	bool _keyboardActive = false;
};
} // namespace cf
