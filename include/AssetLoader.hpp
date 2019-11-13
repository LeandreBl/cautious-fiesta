#pragma once

#include <SFML/Network.hpp>
#include <BasicShape.hpp>

namespace cf
{

    class assetDisplay : public sfs::GameObject
    {
        public:
            assetDisplay(sfs::Scene &scene, const std::string &path) noexcept;
            void start(sfs::Scene &scene) noexcept;
            void changeRec(const sf::Color &color, const int &percentage) noexcept;
            sf::FloatRect getGlobalBounds() noexcept {return _image->getGlobalBounds();};
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