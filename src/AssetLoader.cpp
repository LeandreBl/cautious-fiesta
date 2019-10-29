#include "AssetLoader.hpp"

namespace cf
{

    assetDisplay::assetDisplay(const std::string &path) noexcept
        : _path(path)
        {
            _rectangle = &addComponent<sfs::Rectangle>(sf::Vector2f(0, 0), sf::Vector2f(500, 75), sf::Color(255, 0, 0));
        };

    void assetDisplay::start(sfs::Scene &scene) noexcept
    {
        auto displayVec = scene.getGameObjects<assetDisplay>();
        addComponent<PadderR<assetDisplay>>(170, *this);
        addComponent<PadderT<assetDisplay>>(displayVec.size() * 100, *this);
        auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
        auto texture = scene.getAssetTexture("assets/sprites/Menu/ui/BlankButton2.png");
        _text = &addComponent<sfs::Text>(*font, _path.substr(_path.find_last_of("/\\") + 1), sf::Color::Black, 25);
        auto posX = (_rectangle->getGlobalBounds().width / 2) - (_text->getGlobalBounds().width / 2);
        auto posY = (_rectangle->getGlobalBounds().height / 2) - (_text->getGlobalBounds().height / 2);        
        _text->setOffset(sf::Vector2f(posX, posY));

        _image = &addComponent<sfs::Sprite>(*texture);
        _image->setScale(sf::Vector2f(2, 2));
    }

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
        char buffer[1024];
        std::ofstream file;
        std::size_t rd = 0;
        size_t dl = 0;
        uint8_t colorGreen = 255;
        uint8_t colorRed = 255;

        file.open(path);
        if (!file.is_open())
            std::cerr << "" << std::endl;// TODO error

        auto display = &addChild<assetDisplay>(scene, path);

        do {
            if (_socket.receive(buffer, sizeof(buffer), rd) != sf::Socket::Done)
                std::cerr << "" << std::endl;// TODO error
            file.write(buffer, rd);
            dl += rd;
            colorGreen = (float)dl / size * 255;
            colorRed = 255 - colorGreen;
            display->changeRecColor(sf::Color(colorRed, colorGreen, 0));
        } while (rd);
        file.close();
        _socket.disconnect();
        if (std::filesystem::exists(path) == true && std::filesystem::file_size(path) == size && easyCheckSum(path) == checksum) {
            std::cout << "\nBIEN COPIER\n" << std::endl;
            assetsPath.erase(std::remove(assetsPath.begin(), assetsPath.end(), path));
        } else
            std::filesystem::remove(path);
        //destroy();
    }
}