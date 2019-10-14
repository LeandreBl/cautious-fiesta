#pragma once

#include <GameObject.hpp>
#include <Hnavbar.hpp>
#include <vector>
#include <BasicShape.hpp>
#include <InputBox.hpp>
#include <Button.hpp>
#include "PaddedSprite.hpp"

namespace cf
{
    class rooms : public sfs::GameObject
    {
        public:
            rooms(sfs::Scene &scene, const std::string &name) noexcept 
                : _room(nullptr), _createRoom(nullptr), _box(nullptr), _name(name), _imageCreationRoom(nullptr)
            {
                auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
	            auto texture = scene.getAssetTexture("assets/sprites/Menu/ui/BlankButton2.png");
                _room = &addChild<sfs::Button>(scene, *texture, *font, sf::Vector2f(50, 0),
		                                    std::bind(&rooms::drawGameroom, this, std::ref(scene)),
		                                    _name, sf::Color::White, 25);
                _room->setScale(sf::Vector2f(1.5, 1.5));
            }
            void createRoom(sfs::Scene &) noexcept;
            void drawGameroom(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &) noexcept {
            }
        protected:
            sfs::Button *_room;
            sfs::Button *_createRoom;
            sfs::InputBox *_box;
            std::string _name;
            sfs::Sprite *_imageCreationRoom;
    };

    class RoomSelector : public sfs::GameObject
    {
        public :
            void start(sfs::Scene &scene) noexcept {
                _scrollBar = &addChild<sfs::Hnavbar>(scene, sf::Vector2f(0, 0), sf::Vector2f(30, 1080)); //TODO changer le 1080

                _createButton = &addChild<rooms>(scene, std::ref(scene), "create room");

            }

            void update(sfs::Scene &) noexcept {
            }
        protected:
            sfs::Hnavbar *_scrollBar;
            rooms *_createButton;
    };
}