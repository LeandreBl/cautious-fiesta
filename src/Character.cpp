#include <fstream>
#include "Character.hpp"

namespace cf {

    void CharacterSelector::start(sfs::Scene &scene) noexcept
    {
        _navbar = &addChild<sfs::Hnavbar>(scene, sf::Vector2f(0,0), sf::Vector2f(16, 200), sf::Color::White);
        _navbar->addComponent<PadderW<sfs::Hnavbar>>(-195, *_navbar);
        _navbar->addComponent<PadderH<sfs::Hnavbar>>(50, *_navbar);
        struct Character::stats stats;
        Character testPerso("bob", stats);
        addCharacter(testPerso);
    }

    void CharacterSelector::update(sfs::Scene &scene) noexcept
    {
        if (_characters.size() != 0) {
            float navbarDiv = 1 / (_characters.size() + 1);
            if (_navbar->getValue() == navbarDiv) {
                if (_image == nullptr)
                    _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/CharacterSelection.png"), sf::Vector2f(500, 500));
            }  else {
                 if (_image != nullptr) {
                     _image->destroy();
                     _image = nullptr;
                 }
            }
        }
    }

    void CharacterSelector::loadCharactersFromFile(const std::string &path) noexcept
    {   
        std::ifstream stream;

        stream.open(path);
        if (!stream.is_open())
            return;
        char buffer[4096];
        Serializer s;
        std::streamsize size;
        do {
            size = stream.readsome(buffer, sizeof(buffer));
            if (size < 0)
                return;
            s.nativeSet(buffer, size);
        } while (size == sizeof(buffer));
        while (s.getSize() > 0) {
            std::string name;
            struct Character::stats stats;
            s.get(stats);
            _characters.emplace_back(name, stats);
        }
    }
}