#include "GameManager.hpp"
#include <Padder.hpp>
#include "MenuManager.hpp"
#include "Game.hpp"

namespace cf
{
    void GameManager::start(sfs::Scene &scene) noexcept
    {
        _tcp = &addChild<TcpConnect>(scene, std::ref(scene));
        _udp = &addChild<UdpConnect>(scene);
        _popup = &addChild<sfs::Popup>(scene, *scene.getAssetFont("local-assets/fonts/commodore-64.ttf"));
        _popup->addComponent<PadderR<sfs::Popup>>(-335, *_popup);
        _popup->addComponent<PadderT<sfs::Popup>>(50, *_popup);
    }

    void GameManager::update(sfs::Scene &scene) noexcept
    {
        if (_gameFinished == true)
        {
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
        uint8_t isOk = 0;
        toread.get(isOk);
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
        toread.get(size);
        for (uint64_t i = 0; i != size; i += 1) {
            toread.get(nbPlayers);
            toread.get(roomName);
        }
    }
}