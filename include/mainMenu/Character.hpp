#pragma once

#include <iostream>
#include <vector>
#include <GameObject.hpp>
#include <InputBox.hpp>
#include "Serializer.hpp"
#include "PaddedSprite.hpp"

namespace cf
{
class Character
{
      public:
	struct stats {
		float life = 0;
		float speed = 0;
		float attack = 0;
		float attackSpeed = 0;
		float armor = 0;
	};
	Character(const std::string &name, const struct stats &stats) noexcept
	    : _name(name), _stats(stats){};
	void setName(const std::string &name) noexcept
	{
		_name = name;
	};
	std::string getName() const noexcept
	{
		return _name;
	};
	void setStats(const struct stats &stats) noexcept
	{
		_stats = stats;
	};
	const struct stats &getStats() const noexcept
	{
		return _stats;
	};
	void setLife(float life) noexcept
	{
		_stats.life = life;
	};
	float getLife() const noexcept
	{
		return _stats.life;
	};
	void setSpeed(float speed) noexcept
	{
		_stats.speed = speed;
	};
	float getSpeed() const noexcept
	{
		return _stats.speed;
	};
	void setAttack(float attack) noexcept
	{
		_stats.attack = attack;
	};
	float getAttack() const noexcept
	{
		return _stats.attack;
	};
	void setAttackSpeed(float as) noexcept
	{
		_stats.attackSpeed = as;
	};
	float getAttackSpeed() const noexcept
	{
		return _stats.attackSpeed;
	};
	void setArmor(float armor) noexcept
	{
		_stats.armor = armor;
	};
	float getArmor() const noexcept
	{
		return _stats.armor;
	};

      protected:
	std::string _name;
	struct stats _stats;
};

class Text : public sfs::GameObject
{
      public:
	Text(const sf::Font &font, const std::string &name,
			  const sf::Vector2f &pos, uint32_t size = 18) noexcept
	    : _text(nullptr)
	{
		setPosition(pos);
		_text = &addComponent<sfs::Text>(font, name, sf::Color::White,
						 size);
	}
	void setString(const std::string &str) noexcept
	{
		_text->setString(str);
	}
	sf::FloatRect getGlobalBounds() noexcept 
	{
		return _text->getGlobalBounds();
	}
      protected:
	sfs::Text *_text;
};
} // namespace cf
