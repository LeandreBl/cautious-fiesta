#pragma once

#include <iostream>
#include <vector>
#include <GameObject.hpp>
#include <Hnavbar.hpp>
#include <InputBox.hpp>
#include "Serializer.hpp"
#include "PaddedSprite.hpp"

namespace cf
{
    class Character
    {
        public:
           struct stats {
                int life;
                int speed;
                int attack;
                int attackSpeed;
                int armor;
            };
           Character(const std::string &name, const struct stats &stats) noexcept
                : _name(name), _stats(stats)
                {};
            void setName(const std::string &name) noexcept {_name = name;};
            std::string getName() const noexcept {return _name;};
            void setStats(const struct stats &stats) noexcept {_stats = stats;};
            const struct stats &getStats() const noexcept {return _stats;};
            void setLife(int life) noexcept {_stats.life = life;};
            int getLife() const noexcept {return _stats.life;};
            void setSpeed(int speed) noexcept {_stats.speed = speed;};
            int getSpeed() const noexcept {return _stats.speed;};
            void setAttack(int attack) noexcept {_stats.attack = attack;};
            int getAttack() const noexcept {return _stats.attack;};
            void setAttackSpeed(int as) noexcept {_stats.attackSpeed = as;};
            int getAttackSpeed() const noexcept {return _stats.attackSpeed;};
            void setArmor(int armor) noexcept {_stats.armor = armor;};
            int getArmor() const noexcept {return _stats.armor;};
        protected:
            std::string _name;
            struct stats _stats;
    };

    class CharacterCreation : public sfs::UI
    {
        public:
            CharacterCreation() noexcept
                : _box(nullptr)
                {};
            void start(sfs::Scene &scene) noexcept
            {
                _box = &addChild<sfs::InputBox>(scene, *scene.getAssetFont("assets/fonts/commodore-64.ttf"), sf::Vector2f(0, 200), "[name]", sf::Color::White, 20);
                _box->addComponent<PadderH<sfs::InputBox>>(57, *_box);
                _box->addComponent<PadderW<sfs::InputBox>>(180, *_box);
            }
        protected:
            sfs::InputBox *_box;
            std::string _name;
    };

    class CharacterSelector : public sfs::GameObject
    {
        public:
            CharacterSelector() noexcept
                : _navbar(nullptr), _image(nullptr), _name(nullptr), _creator(nullptr)
                {};
            void start(sfs::Scene &scene) noexcept;
            void update(sfs::Scene &scene) noexcept;
            void addCharacter(Character &character) noexcept {_characters.push_back(character);};
            void loadCharactersFromFile(const std::string &path) noexcept;
            void removeCharacter(const std::string &name) noexcept
                {
                    for (auto it = _characters.begin(); it != _characters.end(); ++it) {
                        if (name == it->getName()) {
                            _characters.erase(it);
                            return;
                        }
                    }
                }
        protected:
            std::vector<Character> _characters;
            sfs::Hnavbar *_navbar;
            sfs::Sprite *_image;
            sfs::Text *_name;
            CharacterCreation *_creator;
    };
}
