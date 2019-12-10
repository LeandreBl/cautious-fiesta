#include "GameManager.hpp"
#include <Padder.hpp>
#include "MenuManager.hpp"
#include "Game.hpp"

namespace cf {
void GameManager::start(sfs::Scene &scene) noexcept
{
	_tcp = &addChild<TcpConnect>(scene, std::ref(scene));
	auto *font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
	if (font == nullptr) {
		std::cerr << "No font set" << std::endl;
		scene.close();
		destroy();
		return;
	}
	_popup = &addChild<sfs::Popup>(scene, *font);
	_popup->addComponent<PadderW<sfs::Popup>>(0, *_popup);
	_popup->addComponent<PadderH<sfs::Popup>>(0, *_popup);
}

void GameManager::update(sfs::Scene &scene) noexcept
{
	if (_gameFinished == true) {
		_gameStarted = false;
		scene.getGameObjects<Game>()[0]->destroy();
		scene.getGameObjects<InputHandler>()[0]->changeGameStarted(false);
		_tcp->disconnect();
		scene.addGameObject<MenuManager>();
		_gameFinished = false;
	}
}

void GameManager::disconnectAndLeaveRoom(Serializer &toread) noexcept
{
	bool isOk = 0;

	toread >> isOk;
	if ((int)isOk == 1 && _gameStarted == true)
		_gameFinished = true;
	else if ((int)isOk == 1 && _gameStarted == false) {
		_ip = "";
		Character charac;
		_character = charac;
	}
}

void GameManager::updateRooms(Serializer &toread) noexcept
{
	uint64_t size = 0;
	uint64_t nbPlayers;
	std::string roomName;
	toread >> size;
	for (uint64_t i = 0; i != size; i += 1) {
		toread >> nbPlayers;
		toread >> roomName;
	}
}
} // namespace cf