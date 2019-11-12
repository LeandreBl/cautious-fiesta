#pragma once

#include "InputBox.hpp"

namespace cf
{
class QuoteGenerator : public sfs::UI
{
      public:
	QuoteGenerator() noexcept
	    : _text(nullptr), _font(nullptr), _scale(1), _rev(1){};
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &scene) noexcept;

      protected:
	sfs::Text *_text;
	const sf::Font *_font;
	float _scale;
	int _rev;
};

class IpInputBox : public sfs::UI
{
      public:
	IpInputBox() noexcept : _input(nullptr){};
	void start(sfs::Scene &scene) noexcept;
	void update(sfs::Scene &) noexcept
	{
		if (_inputOn == true && _input->getSelected() == false) {
			_input->toggle(true);
			_inputOn = false;
		}
	}
	std::string getIp() const noexcept
	{
		return _input->string();
	}
	void activeInputBox() noexcept
	{
		_inputOn = true;
	}

      protected:
	sfs::CustomBox *_input;
	bool _inputOn = false;
};
} // namespace cf
