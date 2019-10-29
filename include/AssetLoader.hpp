#pragma once

#include <SFML/Network.hpp>
#include <GameObject.hpp>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <BasicShape.hpp>
#include "PaddedSprite.hpp"

namespace cf
{

    uint64_t easyCheckSum(const std::string &fileName) noexcept;

    class assetDisplay : public sfs::GameObject
    {
        public:
            assetDisplay(const std::string &path) noexcept;
            void start(sfs::Scene &scene) noexcept;
            void changeRecColor(const sf::Color &color) noexcept {_rectangle->setFillColor(color);};
            sf::FloatRect getGlobalBounds() noexcept {return _rectangle->getGlobalBounds();};
        protected:
            sfs::Rectangle *_rectangle;
            sfs::Text *_text;
            sfs::Sprite *_image;
            const std::string &_path;
    };

    class assetLoader : public sfs::GameObject
    {
        public:
            assetLoader(sfs::Scene &scene, const std::string &path, 
                        const uint16_t &port, const std::string &ip, 
                        const uint64_t &size, const uint64_t &checksum,
                        std::vector<std::string> &assetsPaths) noexcept;
            void dlAsset(sfs::Scene &scene, const std::string &path,
                        const uint64_t &size, const uint64_t &checksum,
                        std::vector<std::string> &assetsPath) noexcept;
        protected:
            sf::TcpSocket _socket;
            sf::Socket::Status _status;
            sf::Thread _dlThread;
    };
}