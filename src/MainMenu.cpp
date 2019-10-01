#include "MainMenu.hpp"

namespace cf
{
void MainMenu::start(sfs::Scene &scene) noexcept
{
	addChild<QuoteGenerator>(scene);
}
} // namespace cf