#include <fstream>
#include "Character.hpp"

namespace cf {

    void CharacterSelector::start(sfs::Scene &scene) noexcept
    {
        _navbar = &addChild<sfs::Hnavbar>(scene, sf::Vector2f(0,0), sf::Vector2f(16, 150), sf::Color::White);
        _navbar->addComponent<PadderW<sfs::Hnavbar>>(-285, *_navbar);
        _navbar->addComponent<PadderH<sfs::Hnavbar>>(46, *_navbar);
        struct Character::stats stats;
        Character testPerso("bob", stats);
        addCharacter(testPerso);
    }

    void CharacterSelector::update(sfs::Scene &scene) noexcept
    {
        if (_characters.size() != 0) {
            float navbarDiv = 1 / (_characters.size() + 1);
            if (_navbar->getValue() == navbarDiv) {
                if (_image == nullptr && _name == nullptr && _nameUi == nullptr) {
                    _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/CharacterSelection.png"), sf::Vector2f(690, 510));
                    _image->setScale(sf::Vector2f(1.2, 1.5));
                    _name = &addComponent<DrawCharacterName>(_characters.at(0), *scene.getAssetFont("assets/fonts/commodore-64.ttf"), sf::Vector2f(1100, 550));
                    _nameUi = &addComponent<sfs::Text>(*scene.getAssetFont("assets/fonts/commodore-64.ttf"), "NAME", sf::Color::White, 20, sf::Vector2f(1110, 528));
                }
            }  else {
                 if (_image != nullptr && _name != nullptr && _nameUi != nullptr) {
                     _image->destroy();
                     _image = nullptr;
                     _name->destroy();
                     _name = nullptr;
                     _nameUi->destroy();
                     _nameUi = nullptr;
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