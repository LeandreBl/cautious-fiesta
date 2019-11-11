#include <Button.hpp>
#include "MenuUi.hpp"
#include <Padder.hpp>

namespace cf
{
static const char *QUOTES[] = {"France number 1",
			       "just ZIBoss117",
			       "Better than Minecraft",
			       "LaMout pd",
			       "I like money",
			       "I <3 Korea",
			       "Better than Fortnite",
			       "The game",
			       "Ryan the king",
			       "France > Korea",
			       "<3 Kakao friends",
			       "Kakao friends > Line Friends",
			       "GOT is overrated",
			       "JBest",
			       "Made in two days",
			       "Hello there",
			       "T-Series > Pwediepie",
			       "Han shot first",
			       "<3 Game software",
			       "Where is Ludo?",
			       "E",
			       "Life solution is 42",
			       "Planard approved",
			       "ASTEK !",
			       "I seoul you",
			       "too fast for u",
			       "The best game",
			       "JOJOOOOO !",
			       "Faster than naruto runners",
			       "Sard AYAYA",
			       "FBI OPEN UP !",
			       "This is a random quote",
			       "Girls, I'm single",
			       "Acmée de la vie"};

void QuoteGenerator::start(sfs::Scene &scene) noexcept
{
	setPosition(sf::Vector2f(200, 200));
	_font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	if (_font == nullptr) {
		errorLog("Required font not found.");
		destroy();
		return;
	}
	std::srand(time(nullptr));
	_text = &addComponent<sfs::Text>(
		*_font, QUOTES[rand() % (sizeof(QUOTES) / sizeof(QUOTES[0]))],
		sf::Color::Yellow, 40);
}

void QuoteGenerator::update(sfs::Scene &scene) noexcept
{
	auto dt = scene.deltaTime();
	auto max = 1.f / scene.framerate();
	if (dt > max)
		dt = max;
	_scale += 0.35 * dt * _rev;
	if (_scale > 1 || _scale < 0.3) {
		_rev *= -1;
		_text->setString(std::string(
			QUOTES[rand() % (sizeof(QUOTES) / sizeof(QUOTES[0]))]));
	}
	_text->setScale(_scale, _scale);
}

void IpInputBox::start(sfs::Scene &scene) noexcept
{
	auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	auto texture = scene.getAssetTexture(
		"local-assets/sprites/Menu/ui/BlankButton1.png");
	if (font == nullptr || texture == nullptr) {
		errorLog(
			"[Menu] The InputBox failed the loading of the font or the texture");
		destroy();
		return;
	}

	auto &button = addChild<sfs::Button>(scene, *texture, *font);
	button.setScale(sf::Vector2f(1.5, 2.2));
	button.addComponent<PadderW<sfs::Button>>(0, button);
	button.addComponent<PadderH<sfs::Button>>(-100, button);

	_input = &addChild<sfs::CustomBox>(scene, *font, sf::Vector2f(0, 0),
					   "IP", sf::Color::White, 35,
					   "1234567890.");
	_input->addComponent<PadderW<sfs::InputBox>>(0, *_input);
	_input->addComponent<PadderH<sfs::InputBox>>(-110, *_input);
}
} // namespace cf
