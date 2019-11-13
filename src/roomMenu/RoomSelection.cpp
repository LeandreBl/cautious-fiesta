#include "RoomSelection.hpp"

namespace cf
{
    RoomSelector::RoomSelector(sfs::Scene &scene) noexcept
        :_scene(scene)
    {
        _createButton = &addChild<roomList>(scene, std::ref(scene));
    }

    void RoomSelector::handleRoomList(Serializer &toread) noexcept
    {
       uint64_t size = 0;
        uint64_t nbPlayers;
        std::string roomName;
        toread.get(size);
        _createButton->destroyRooms();
        for (uint64_t i = 0; i != size; i += 1) {
            toread.get(nbPlayers);
            toread.get(roomName);
            _createButton->addRoom(_scene, roomName, i + 1, nbPlayers);
            if (_createButton->getPosition().y >= 950 && _scrollBar == nullptr)
                _scrollBar = &addChild<sfs::Vnavbar>(_scene, sf::Vector2f(0, 0), sf::Vector2f(30, 1080));
            else if (_createButton->getPosition().y < 950 && _scrollBar != nullptr) {
                _scrollBar->destroy();
                _scrollBar = nullptr;
            }
        }
    }

    void RoomSelector::update(sfs::Scene &) noexcept
    {
        if (_scrollBar != nullptr)
            if (lockScrollBar != _scrollBar->getValue()) {
                float pos = (_createButton->getHeight() -950) * _scrollBar->getValue();
                _createButton->setPosition(sf::Vector2f(0, _createButton->getHeight() - pos));
                lockScrollBar = _scrollBar->getValue();
            }
    }

    sf::Vector2f RoomSelector::RoomListPos() noexcept
    {
        return _createButton->getPosition();
    }
}