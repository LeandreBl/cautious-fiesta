#include <iostream>
#include "MainMenu.hpp"

namespace cf
{

  static const char *QUOTES[] = {"France number 1", "just ZIBoss117", "Better than Minecraft", "Lamout pd", "I like money", "I <3 Korea",
				 "Better than Fortnite", "The game", "Ryan the king", "France > Korea", "<3 Kakao friends", "Kakao friends > Line Friends",
				 "GOT is overrated", "JBest", "Made in two days", "Hello there", "T-Series > Pwediepie", "Han shot first", "<3 Game software",
				 "Where is Ludo?", "E", "Life solution is 42", "Planard approved", "ASTEK !", "I seoul you", "too fast for u", "The best game",
				 "JOJOOOOO !", "Faster than naruto runners", "Sard AYAYA", "FBI OPEN UP !", "This is a random quote", "Girls, I'm single"};

  void QuoteGenerator::start(sfs::Scene &scene) noexcept
  {
    setPosition(sf::Vector2f(200, 200));
    _font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
    std::srand(time(nullptr));
    _text = &addComponent<sfs::Text>(*_font, QUOTES[rand() % (sizeof(QUOTES) / sizeof(QUOTES[0]))], sf::Color::Yellow, 40);
  }

  void QuoteGenerator::update(sfs::Scene &scene) noexcept
  {
    _scale += 0.5 * scene.deltaTime() * _rev;
    if (_scale > 1 || _scale < 0.3) {
      _rev *= -1;
      _text->setString(std::string(QUOTES[rand() % (sizeof(QUOTES) / sizeof(QUOTES[0]))]));
    }
    _text->setScale(_scale, _scale);
  }
  
  
  void ExitButton::closeScene(sfs::Scene &scene) const noexcept
  {
    scene.close();
  }

  void ExitButton::start(sfs::Scene &scene) noexcept
  {
    auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
    auto texture = scene.getAssetTexture("assets/sprites/blank.png");
    
    if (font == nullptr || texture == nullptr) {
      errorLog("[Menu] could not load the font or the texture");
      scene.close();
    }

    auto &button = addChild<sfs::Button>(scene,
					 sf::Vector2f(0, 0),
					 *texture,
					 std::bind(&ExitButton::closeScene, this, std::ref(scene)),
					 *font,
					 "Quit",
					 sf::Color::White,
					 22);
    
    button.addComponent<PadderL<sfs::Button>>(25.f, button);
    button.addComponent<PadderB<sfs::Button>>(25.f, button);
    
    button.setScale(sf::Vector2f(1, 1.5));
  }

  void OptionsButton::OptionScene() noexcept
  {
    std::cout << "options activées" << std::endl;
  }
  
  void OptionsButton::start(sfs::Scene &scene) noexcept
  {
    auto font = scene.getAssetFont("assets/fonts/commodore-64.ttf");
    auto texture = scene.getAssetTexture("assets/sprites/blank.png");
    
    if (font == nullptr || texture == nullptr) {
      errorLog("[Menu] could not load the font or the texture");
      scene.close();
    }
    
    auto &button = addChild<sfs::Button>(scene,
					 sf::Vector2f(0, 0),
					 *texture,
					 std::bind(&OptionsButton::OptionScene, this),
					 *font,
					 "Options",
					 sf::Color::White,
					 22);
    
    button.addComponent<PadderR<sfs::Button>>(25.f, button);
    button.addComponent<PadderB<sfs::Button>>(25.f, button);
    
    button.setScale(sf::Vector2f(1, 1.5));
  }
  
  void NavBar::start(sfs::Scene &scene) noexcept
  {
    auto &navbar = addChild<sfs::Hnavbar>(scene, sf::Vector2f(0,0),
    					  sf::Vector2f(150, 150),
    					  sf::Color::White);

    navbar.addComponent<PadderL<sfs::Hnavbar>>(150, navbar);
    navbar.addComponent<PadderT<sfs::Hnavbar>>(150, navbar);
  }
  
  
  void MainMenu::start(sfs::Scene &scene) noexcept
  {

    //auto backTexture = scene.getAssetTexture("/home/jb/Projets/cautious-fiesta/assets/menu.png");
    //_background = &addComponent<sfs::Sprite>(*backTexture);
    //_background->setScale(2, 4);
    
    addChild<QuoteGenerator>(scene);
    addChild<ExitButton>(scene);
    addChild<OptionsButton>(scene);
    //addChild<NavBar>(scene); padder fonctionne pas
    scene.subscribe(*this, sf::Event::Closed);
  }

  void MainMenu::onEvent(sfs::Scene &scene, const sf::Event &event) noexcept
  {
    if (event.type == sf::Event::Closed)
      scene.close();
  }
  
  void MainMenu::update(sfs::Scene &scene) noexcept
  {
   
  }
} // namespace cf
