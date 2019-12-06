#pragma once

#include "MenuButtons.hpp"
#include "MenuBackgrounds.hpp"
#include "MenuUi.hpp"
#include "Option.hpp"

namespace cf {
class MainMenu : public sfs::GameObject {
      public:
	MainMenu(Scroller *scroller) noexcept
		: _scroller(scroller)
		, _play(nullptr)
		, _quotes(nullptr)
		, _exit(nullptr)
		, _options(nullptr)
		, _optionImage(nullptr)
		, _opS(nullptr){};
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;
	void createOptionsButton(sfs::Scene &scene) noexcept;
	void launchOptionScene(sfs::Scene &scene) noexcept;

      protected:
	Scroller *_scroller;
	PlayButton *_play;
	QuoteGenerator *_quotes;
	ExitButton *_exit;
	sfs::Button *_options;
	Background *_optionImage;
	optionScene *_opS;
};
} // namespace cf
