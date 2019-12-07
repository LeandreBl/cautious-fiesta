#include "SpriteSheetLoader.hpp"
#include <filesystem>
#include <fstream>

namespace cf
{
    SpriteSheetLoader::SpriteSheetLoader(const std::string &path) noexcept
    {
        if (std::filesystem::exists(path) == true) {
            std::ifstream stream;

            stream.open(path);
            if (stream.is_open() == true) {
                std::string line;

                while (std::getline(stream, line)) {
                    std::istringstream iss(line);
                    sf::IntRect frame;

                    iss >> frame.width >> frame.height >> frame.top >> frame.left;
                    _frames.emplace_back(frame);
                }
                stream.close();
            }
        }
    }
}