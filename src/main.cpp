#include <WScene.hpp>
#include <GameObject.hpp>

class BasicHandler : public sfs::GameObject {
	public:
	void start(sfs::Scene &scene) noexcept
	{
		scene.subscribe(*this, sf::Event::Closed);
	}
	void onEvent(sfs::Scene &scene, const sf::Event &) noexcept
	{
		scene.close();
	}
};

int main()
{
	sfs::WScene scene("cautious_fiesta", 120);

	scene.addGameObject<BasicHandler>();
	scene.run();
	return 0;
}
