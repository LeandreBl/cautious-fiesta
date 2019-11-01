#include "GameManager.hpp"
#include "PaddedSprite.hpp"
#include "MenuManager.hpp"

namespace cf
{
    void GameManager::start(sfs::Scene &scene) noexcept
    {
        _tcp = &addChild<TcpConnect>(scene);
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
            _game->destroy();
            _game = nullptr;
            _tcp->disconnect();
            scene.addGameObject<MenuManager>();
            _gameFinished = false;
        }
    }

    void GameManager::leaveRoomAfterTheGameStarted(Serializer &toread) noexcept
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
}