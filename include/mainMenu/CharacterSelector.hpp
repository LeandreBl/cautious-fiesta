#pragma once

#include <vector>
#include <GameObject.hpp>
#include <Hnavbar.hpp>
#include "Character.hpp"
#include "CharacterCreator.hpp"

namespace cf
{
  class CharacterSelector : public sfs::GameObject
  {
  public:
    CharacterSelector() noexcept
    : _navbar(nullptr), _image(nullptr), _name(nullptr),
      _creator(nullptr){};
    void start(sfs::Scene &scene) noexcept;
    void update(sfs::Scene &scene) noexcept;
    Character charaterSelected() noexcept {
      if (_creator != nullptr) {
        auto newCharacter = _creator->createCharacter();
        addCharacter(newCharacter);
        return newCharacter;
      }
      float characterSelected = _characters.size() * _navbar->getValue();
      return _characters.at((int)characterSelected);
    };
    void addCharacter(const Character &character) noexcept
    {
      _characters.emplace_back(character);
    };
    void loadCharactersFromFile(const std::string &path) noexcept;
  protected:
    std::vector<Character> _characters;
    sfs::Hnavbar *_navbar;
    sfs::Sprite *_image;
    sfs::Text *_name;
    CharacterCreation *_creator;
  };
}
