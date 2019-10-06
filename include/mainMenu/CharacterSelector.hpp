#pragma once

#include <vector>
#include <GameObject.hpp>
#include <Hnavbar.hpp>
#include <Button.hpp>
#include "Character.hpp"
#include "CharacterCreator.hpp"

namespace cf
{
  class CharacterSelector : public sfs::GameObject
  {
  public:
    CharacterSelector(const std::string &path) noexcept
    : _navbar(nullptr), _image(nullptr), _name(nullptr),
      _creator(nullptr), _path(path) {};
    void start(sfs::Scene &scene) noexcept;
    void update(sfs::Scene &scene) noexcept;
    Character charaterSelected() noexcept {
      if (_creator != nullptr) {
        return _creator->createCharacter();
      }
      float characterSelected = _characters.size() * _navbar->getValue();
      return _characters.at((int)characterSelected);
    };
    void addCharacter(const Character &character) noexcept
    {
      _characters.emplace_back(character);
    };
    void loadCharactersFromFile() noexcept;
    void writeCharacterInFile() noexcept;
    void addCharacterFromCreateButton() noexcept
    {
      if (_creator != nullptr) {
        _characters.emplace_back(_creator->createCharacter());
        writeCharacterInFile();
      }
    }
  protected:
    std::vector<Character> _characters;
    sfs::Hnavbar *_navbar;
    sfs::Sprite *_image;
    sfs::Text *_name;
    CharacterCreation *_creator;
    std::string _path;
  };
}
