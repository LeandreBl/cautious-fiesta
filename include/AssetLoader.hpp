#pragma once

#include <SFML/Network.hpp>
#include <GameObject.hpp>
#include <algorithm>
#include <fstream>
#include <filesystem>

namespace cf
{

    uint64_t easyCheckSum(const std::string &fileName) noexcept;

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