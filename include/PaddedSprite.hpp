#pragma once

#include <SFML/System.hpp>
#include <IComponent.hpp>

namespace cf
{
template <typename T> class PadderR : public sfs::IComponent
{
      public:
	PadderR(float offset, T &object) noexcept
	    : _object(object), _offset(offset)
	{
	}
	void display(sf::RenderWindow &window) noexcept
	{
		auto pos = _object.getPosition();
		pos.x = window.getSize().x - _offset
			- _object.getGlobalBounds().width;
		_object.setPosition(pos);
	}

      protected:
	T &_object;
	float _offset;
};


template <typename T> class PadderL : public sfs::IComponent
{
      public:
	PadderL(float offset, T &object) noexcept
	    : _object(object), _offset(offset)
	{
	}
	void display(sf::RenderWindow &window[[gnu::unused]]) noexcept
	{
		auto pos = _object.getPosition();
		pos.x = _offset;
		_object.setPosition(pos);
	}

      protected:
	T &_object;
	float _offset;
};


template <typename T> class PadderT : public sfs::IComponent
{
      public:
	PadderT(float offset, T &object) noexcept
	    : _object(object), _offset(offset)
	{
	}
	void display(sf::RenderWindow &window[[gnu::unused]]) noexcept
	{
		auto pos = _object.getPosition();
		pos.y = _offset;
		_object.setPosition(pos);
	}

      protected:
	T &_object;
	float _offset;
};

template <typename T> class PadderB : public sfs::IComponent
{
      public:
	PadderB(float offset, T &object) noexcept
	    : _object(object), _offset(offset)
	{
	}
	void display(sf::RenderWindow &window) noexcept
	{
		auto pos = _object.getPosition();
		pos.y = window.getSize().y - _offset
			- _object.getGlobalBounds().height;
		_object.setPosition(pos);
	}

      protected:
	T &_object;
	float _offset;
};

template <typename T> class PadderH : public sfs::IComponent
{
      public:
	PadderH(float offset, T &object) noexcept
	    : _object(object), _offset(offset)
	{
	}
	void display(sf::RenderWindow &window) noexcept
	{
		auto pos = _object.getPosition();
		pos.y = (window.getSize().y / 2)
			- (_object.getGlobalBounds().height / 2) + _offset;
		_object.setPosition(pos);
	}

      protected:
	T &_object;
	float _offset;
};

template <typename T> class PadderW : public sfs::IComponent
{
      public:
	PadderW(float offset, T &object) noexcept
	    : _object(object), _offset(offset)
	{
	}
	void display(sf::RenderWindow &window) noexcept
	{
		auto pos = _object.getPosition();
		pos.x = (window.getSize().x / 2)
			- (_object.getGlobalBounds().width / 2) + _offset;
		_object.setPosition(pos);
	}

      protected:
	T &_object;
	float _offset;
};
} // namespace cf
