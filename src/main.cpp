#include <WScene.hpp>
#include "MenuManager.hpp"

int main()
{
	sfs::WScene scene("cautious_fiesta", 120);

	scene.addGameObject<cf::GameManager>();
	scene.addGameObject<cf::MenuManager>();
	scene.run();
	return 0;
}