#include <WScene.hpp>
#include <GameObject.hpp>

#include "MainMenu.hpp"

int main()
{
	sfs::WScene scene("cautious_fiesta", 120);

	scene.addGameObject<cf::MainMenu>();
	scene.run();
	return 0;
}
