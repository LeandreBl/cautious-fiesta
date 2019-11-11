#include <fstream>
#include <filesystem>
#include "AssetLoader.hpp"
#include <Padder.hpp>

namespace cf
{

    assetDisplay::assetDisplay(sfs::Scene &scene, const std::string &path) noexcept
        : _path(path)
    {
        setPosition(sf::Vector2f(-1000, -1000));
        auto font = scene.getAssetFont("local-assets/fonts/commodore-64.ttf");
        auto texture = scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png");
        _image = &addComponent<sfs::Sprite>(*texture);
        _image->setScale(sf::Vector2f(1.2, 1.2));

        _text = &addComponent<sfs::Text>(*font, _path.substr(_path.find_last_of("/\\") + 1), sf::Color::White, 15);
        _text->setOffset(sf::Vector2f(_image->getPosition().x, _image->getPosition().y - 20));

        _rectangle = &addComponent<sfs::Rectangle>(sf::Vector2f(0, 0), sf::Vector2f(420, 50), sf::Color(255, 0, 0));
        auto posX = (_image->getGlobalBounds().width / 2) - (_rectangle->getGlobalBounds().width / 2);
        auto posY = (_image->getGlobalBounds().height / 2) - (_rectangle->getGlobalBounds().height / 2);
        _rectangle->setOffset(sf::Vector2f(posX, posY));
    };

    void assetDisplay::start(sfs::Scene &scene) noexcept
    {
        auto displayVec = scene.getGameObjects<assetDisplay>();
        addComponent<PadderR<assetDisplay>>(170, *this);
        addComponent<PadderT<assetDisplay>>(displayVec.size() * 110, *this);
    }

    void assetDisplay::changeRec(const sf::Color &color, const int &percentage) noexcept
    {
        _rectangle->setFillColor(color);
        _rectangle->setSize(sf::Vector2f((420 * percentage) / 100, 50));
    }

    assetLoader::assetLoader(sfs::Scene &scene, const std::string &path,
                            const uint16_t &port, const std::string &ip,
                            const uint64_t &size, const uint64_t &checksum,
                            std::vector<std::string> &assetsPaths) noexcept
        : _dlThread(std::bind(&assetLoader::dlAsset, this, std::ref(scene), path, size, checksum, std::ref(assetsPaths)))
    {
        _status = _socket.connect(ip, port);
        if (_status != sf::Socket::Done) {
            std::cout << "fail to connect" << std::endl;
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

        auto display = &addChild<assetDisplay>(scene, std::ref(scene), path);

        do {
            if (sizeof(buffer) > size - dl) {
                if (_socket.receive(buffer, size - dl, rd) != sf::Socket::Done)
                    std::cerr << "" << std::endl;// TODO error
           } else
                if (_socket.receive(buffer, sizeof(buffer), rd) != sf::Socket::Done)
                    std::cerr << "" << std::endl;// TODO error
            file.write(buffer, rd);
            dl += rd;
            colorGreen = (float)dl / size * 255;
            colorRed = 255 - colorGreen;
            display->changeRec(sf::Color(colorRed, colorGreen, 0), (dl * 100) / size);
        } while (dl < size); //avant c'était juste rd
        file.close();
        _socket.disconnect();
        if (std::filesystem::exists(path) == true && std::filesystem::file_size(path) == size && easyCheckSum(path) == checksum) {
            std::cout << "\nBIEN COPIER\n" << std::endl;
            assetsPath.erase(std::remove(assetsPath.begin(), assetsPath.end(), path));
        } else { //TODO trouver une solution quand c'est pas bon car du coup le vecteur de path est pas vidé
            std::cout << "NEIN" << std::endl;
            std::cout << "file exits ? : " << std::filesystem::exists(path)
            << "\nfile size : " << std::filesystem::file_size(path) << " true size : " << size
            << "\ncheckSum : " << easyCheckSum(path) << " true checkSum : " << checksum << std::endl;
            std::filesystem::remove(path);
        }
        destroy();
    }
}