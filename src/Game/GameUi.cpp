#include "GameUi.hpp"

namespace cf {
GameUi::GameUi(sfs::Scene &scene) noexcept
	: sfs::UI(sf::Vector2f(), "GameUi")
	, _chat(nullptr)
	, _life(nullptr)
{
	_chat = &addChild<Chat>(scene, 3);
	_life = &addChild<Life>(scene);
}
}