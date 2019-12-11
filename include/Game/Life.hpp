#pragma once

#include <UI.hpp>
#include <BasicShape.hpp>

namespace cf
{
    class Life : public sfs::UI
    {
        public:
            Life(uint64_t id) noexcept;
            void start(sfs::Scene &scene) noexcept;
            void changeLife(float life, uint64_t id) noexcept;
        protected:
            float _maxLife;
            sfs::Sprite *_heart;
            sfs::Text *_lifeDisplay;
            std::vector<sf::IntRect> _frames;
            uint64_t _id;
    };
}