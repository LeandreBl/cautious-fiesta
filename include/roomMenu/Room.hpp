#pragma once

#include <UI.hpp>
#include <BasicShape.hpp>

namespace cf
{
    class Room : public sfs::UI
    {
        public:
            void start(sfs::Scene &scene) noexcept;
            void setImage(const std::string &name) noexcept;
            void hideImage() noexcept;
        protected:
            sfs::Sprite *_image = nullptr;
            sfs::Text *_roomName = nullptr;
    };
}