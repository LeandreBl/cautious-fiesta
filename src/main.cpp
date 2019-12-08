#include <WScene.hpp>
#include "MenuManager.hpp"
#include "InputHandler.hpp"

int main()
{
	sfs::WScene scene("cautious_fiesta", 120);

	scene.vSync(true);
	scene.addGameObject<cf::GameManager>();
	scene.addGameObject<cf::MenuManager>();
	scene.addGameObject<cf::InputHandler>();
	scene.run();
	return 0;
}