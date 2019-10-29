#include "AssetLoader.hpp"

namespace cf
{
    assetLoader::assetLoader(sfs::Scene &scene, const std::string &path, 
                            const uint16_t &port, const std::string &ip, 
                            const uint64_t &size, const uint64_t &checksum,
                            std::vector<std::string> &assetsPaths) noexcept
        : _dlThread(std::bind(&assetLoader::dlAsset, this, std::ref(scene), path, size, checksum, std::ref(assetsPaths)))
    {
        _status = _socket.connect(ip, port);
        if (_status != sf::Socket::Done) {
            destroy();
            return ;
        }
        _socket.setBlocking(false);
        _dlThread.launch();
    }

    void assetLoader::dlAsset(sfs::Scene &scene, const std::string &path, const uint64_t &size, const uint64_t &checksum, std::vector<std::string> &assetsPath) noexcept
    {
        (void)scene; //TODO un truc graphic qui montre le dl genre une bar
        char buffer[1024];
        std::ofstream file;
        std::size_t rd = 0;
        file.open(path);
        if (!file.is_open())
            std::cerr << "" << std::endl;// TODO error
        do {
            if (_socket.receive(buffer, sizeof(buffer), rd) != sf::Socket::Done)
                std::cerr << "" << std::endl;// TODO error
            file.write(buffer, rd);
        } while (rd);
        file.close();
        _socket.disconnect();
        if (std::filesystem::exists(path) == true && std::filesystem::file_size(path) == size && easyCheckSum(path) == checksum) {
            std::cout << "\nBIEN COPIER\n" << std::endl;
            assetsPath.erase(std::remove(assetsPath.begin(), assetsPath.end(), path));
        } else
            std::filesystem::remove(path);
        destroy();
    }
}