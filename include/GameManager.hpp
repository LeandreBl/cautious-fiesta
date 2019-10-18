#pragma once

#include <iostream>
#include <GameObject.hpp>
#include <Popup.hpp>
#include "Character.hpp"
#include "TcpConnection.hpp"
#include "PaddedSprite.hpp"

namespace cf
{
    class GameManager : public sfs::GameObject
    {
        public :
            void start(sfs::Scene &scene) noexcept
            {
              _tcp = &addChild<TcpConnect>(scene);
              _popup = &addChild<sfs::Popup>(scene, *scene.getAssetFont("assets/fonts/commodore-64.ttf"));
              _popup->addComponent<PadderR<sfs::Popup>>(-335, *_popup);
              _popup->addComponent<PadderT<sfs::Popup>>(50, *_popup);
            }
            Character _character;
            std::string _ip = "";
            TcpConnect *_tcp = nullptr;
            sfs::Popup *_popup = nullptr;
    };
}