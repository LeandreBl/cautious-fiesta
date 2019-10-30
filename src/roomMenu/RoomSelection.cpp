#include "RoomSelection.hpp"

namespace cf
{
    RoomSelector::RoomSelector(sfs::Scene &scene) noexcept
        :_scene(scene)
        {
        };

    void RoomSelector::start(sfs::Scene &scene) noexcept
    {
        _createButton = &addChild<roomList>(scene, std::ref(scene));
    }

    void RoomSelector::drawRooms(std::vector<std::pair<uint64_t, std::string>> rooms) noexcept
    {
        if (_createButton != nullptr) {
            _createButton->destroyRooms();
            for (size_t i = 0; i < rooms.size(); i += 1) {
                _createButton->addRoom(_scene, rooms[i].second, i + 1, rooms[i].first);
                if (_createButton->getPosition().y >= 950 && _scrollBar == nullptr)
                    _scrollBar = &addChild<sfs::Hnavbar>(_scene, sf::Vector2f(0, 0), sf::Vector2f(30, 1080));
                else if (_createButton->getPosition().y < 950 && _scrollBar != nullptr) {
                    _scrollBar->destroy();
                    _scrollBar = nullptr;
                }
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

    void RoomSelector::destroyRoom() noexcept
    {
        _createButton->HideRoom();
    }

    void RoomSelector::updatePlayerInRoom(std::vector<std::pair<uint64_t, std::string>> players, uint8_t ready) noexcept
    {
        _createButton->updatePlayerInRoom(players, ready);
    }

    sf::Vector2f RoomSelector::RoomListPos() noexcept
    {
        return _createButton->getPosition();
    }
}