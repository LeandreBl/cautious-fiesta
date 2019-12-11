#include "GameUi.hpp"

namespace cf {
GameUi::GameUi(sfs::Scene &scene) noexcept
	: sfs::UI(sf::Vector2f(), "GameUi")
	, _chat(nullptr)
	, _weapon(nullptr)
{
	_chat = &addChild<Chat>(scene, 3);
	_weapon = &addChild<UiWeapon>(scene);
}
}