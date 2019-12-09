#include <Button.hpp>
#include "MenuUi.hpp"
#include <Padder.hpp>

namespace cf {
static const char *QUOTES[] = {
	"just ZIBoss",
	"Better than Minecraft",
	"LaMout pd",
	"I like money",
	"I <3 Korea",
	"Better than Fortnite",
	"The game",
	"Ryan the king",
	"<3 Kakao friends",
	"GOT is overrated",
	"Made in two days",
	"Hello there",
	"PewDiePie > T-Series",
	"Han shot first",
	"<3 Game software",
	"Where is Ludo?",
	"E",
	"Life solution is 42",
	"Planard approved",
	"ASTEK !",
	"I Seoul U",
	"The best game",
	"Sard AYAYA",
	"FBI OPEN UP !",
	"\"This is a random quote\"",
	"Girls, I'm single",
	"Acmee de la vie",
};

void QuoteGenerator::start(sfs::Scene &scene) noexcept
{
	_font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	if (_font == nullptr) {
		errorLog("Required font not found.");
		destroy();
		return;
	}
	std::srand(time(nullptr));
	_text = &addComponent<sfs::Text>(*_font,
					 QUOTES[rand() % (sizeof(QUOTES) / sizeof(QUOTES[0]))],
					 sf::Color::Yellow, 40);
	auto *texture = scene.getAssetTexture("local-assets/sprites/cautious-fiesta.png");
	if (texture == nullptr) {
		std::cerr << "Can't find cautious-fiesta.png" << std::endl;
		scene.close();
		return;
	}
	addComponent<sfs::Sprite>(*texture, -getPosition());
}

void QuoteGenerator::update(sfs::Scene &scene) noexcept
{
	auto dt = scene.deltaTime();
	auto max = 1.f / scene.framerate();
	if (dt > max)
		dt = max;
	_scale += 0.75 * dt * _rev;
	if (_scale > 1 || _scale < 0.01) {
		_rev *= -1;
		_swap = !_swap;
		if (_swap == false) {
			_text->setString(
				std::string(QUOTES[rand() % (sizeof(QUOTES) / sizeof(QUOTES[0]))]));
		}
	}
	_text->setScale(_scale, _scale);
}

void IpInputBox::start(sfs::Scene &scene) noexcept
{
	auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	auto texture = scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton1.png");
	if (font == nullptr || texture == nullptr) {
		errorLog("[Menu] The InputBox failed the loading of the font or the texture");
		destroy();
		return;
	}

	auto &button = addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(-1000, -1000),
					     std::bind(&IpInputBox::activeInputBox, this));
	button.setScale(sf::Vector2f(1.5, 2.2));
	button.addComponent<PadderW<sfs::Button>>(0, button);
	button.addComponent<PadderH<sfs::Button>>(-100, button);

	_input = &addChild<sfs::CustomBox>(scene, *font, sf::Vector2f(0, 0), "IP", sf::Color::White,
					   35, "1234567890.");
	_input->addComponent<PadderW<sfs::InputBox>>(0, *_input);
	_input->addComponent<PadderH<sfs::InputBox>>(-110, *_input);
}
} // namespace cf
