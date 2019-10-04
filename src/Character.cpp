#include <fstream>
#include <iostream>
#include "Character.hpp"

namespace cf {

  void CharacterSelector::start(sfs::Scene &scene) noexcept
  {
    _navbar = &addChild<sfs::Hnavbar>(scene, sf::Vector2f(0,0), sf::Vector2f(16, 150), sf::Color::White);
    _navbar->addComponent<PadderW<sfs::Hnavbar>>(-285, *_navbar);
    _navbar->addComponent<PadderH<sfs::Hnavbar>>(46, *_navbar);
	  _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("assets/sprites/CharacterSelection.png"), sf::Vector2f(690, 510));
	  _image->setScale(sf::Vector2f(1.2, 1.5));
	  _nameUi = &addComponent<sfs::Text>(*scene.getAssetFont("assets/fonts/commodore-64.ttf"), "NAME", sf::Color::White, 20, sf::Vector2f(1110, 528));
    struct Character::stats stats;
    Character testPerso("bob", stats);
    Character leandre("leandre", stats);
    Character jb("jb", stats);
    addCharacter(testPerso);
    addCharacter(leandre);
    //addCharacter(jb);
  }
  
  void CharacterSelector::update(sfs::Scene &scene) noexcept
  {
    if (_characters.size() != 0) {
      float characterSelected = _characters.size() * _navbar->getValue();
      if (_navbar->getValue() < 1) {
          if (_name == nullptr) {
	          _name = &addComponent<DrawCharacterName>(_characters.at((int)characterSelected), *scene.getAssetFont("assets/fonts/commodore-64.ttf"), sf::Vector2f(1082, 590));
          } else {
            _name->setString(_characters.at((int)characterSelected).getName());
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
