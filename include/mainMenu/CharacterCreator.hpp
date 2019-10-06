#pragma once

#include <vector>
#include <InputBox.hpp>
#include "Character.hpp"

namespace cf {
    class CharacterCreation : public sfs::UI
{
    public:
		CharacterCreation() noexcept : _boxName(nullptr), _printTotal(nullptr) {};
    	void start(sfs::Scene &scene) noexcept;	
    	void update(sfs::Scene &scene) noexcept;		
    	void onEvent(sfs::Scene &, const sf::Event &event) noexcept;
    	Character createCharacter() noexcept;
    protected:
		sfs::InputBox *_boxName;
		std::vector<sfs::CustomBox *> _stats;
  		CharacterStatName *_printTotal;
		float _total = 100;
};
}