#pragma once

#include <GameObject.hpp>
#include <WScene.hpp>
#include <Button.hpp>

namespace cf
{
//phrases random 1
class QuoteGenerator : public sfs::GameObject
{
	public:
	protected:
};

//init 0 (créer les autres Go)
class MainMenu : public sfs::GameObject
{
      public:
	  void start(sfs::Scene &scene) noexcept;
	  void update(sfs::Scene &scene) noexcept;
      protected:
};
} // namespace cf