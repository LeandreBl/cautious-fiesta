#pragma once

#include <GameObject.hpp>
#include <Velocity.hpp>
#include <BasicShape.hpp>

namespace cf
{
 class Background : public sfs::GameObject
    {
        public:
            Background(const std::string &path = "") noexcept
                : _image(nullptr), _velo(nullptr), _path(path)
                {};
            void start(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &) noexcept;
            sf::FloatRect getGlobalBounds() noexcept;
            void addVelocity(sf::Vector2f speed) noexcept;
        protected:
            sfs::Sprite *_image;
            sfs::Velocity *_velo;
            std::string _path;
            bool _lock = false;
    };   

    class Text : public sfs::GameObject
{
      public:
        Text(const sf::Font &font, const std::string &name,
			  const sf::Vector2f &pos, uint32_t size = 18) noexcept;
        void setString(const std::string &str) noexcept;
	    sf::FloatRect getGlobalBounds() noexcept;
      protected:
	sfs::Text *_text;
};
}