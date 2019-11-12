#pragma once

#include <vector>
#include <Vnavbar.hpp>
#include "CharacterCreator.hpp"

namespace cf
{
  class CharacterSelector : public sfs::GameObject
  {
  public:
    CharacterSelector(const std::string &path) noexcept
    : _navbar(nullptr), _image(nullptr), _name(nullptr),
      _creator(nullptr), _path(path), _hat(nullptr) {};
    void start(sfs::Scene &scene) noexcept;
    void update(sfs::Scene &scene) noexcept;
    Character charaterSelected() noexcept {
      if (_creator != nullptr) {
        auto newCharacter = _creator->createCharacter();
        if (newCharacter.getName() != "noName") {
          addCharacter(newCharacter);
          writeCharacterInFile();
        }
        return newCharacter;
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
        auto _new = _creator->createCharacter();
        if (_new.getName() != "noName") {
          _characters.emplace_back(_new);
          writeCharacterInFile();
          _creator->destroy();
          _creator = nullptr;
        }
      }
    }
  protected:
    std::vector<Character> _characters;
    sfs::Vnavbar *_navbar;
    sfs::Sprite *_image;
    sfs::Text *_name;
    CharacterCreation *_creator;
    std::string _path;
    std::vector<Text *> _stats;
    sfs::Sprite *_hat;
  };
}
