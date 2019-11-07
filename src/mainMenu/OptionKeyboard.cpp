#include <Offset.hpp>
#include "Option.hpp"
#include "PaddedSprite.hpp"

namespace cf
{
    std::vector<std::string> keys = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
        "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Escape", "LControl", "LShift", "LAlt", "LSystem",
        "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket", "RBracket", "Semicolon", "Comma", "Period", "Quote", "Slash", "Backslash",
        "Tilde", "Equal", "Hyphen", "Space", "Enter", "Backspace", "Tab", "PageUp", "PageDown", "End", "Home", "Insert", "Delete", "Add",
        "Subtract", "Multiply", "Divide", "Left", "Right", "Up", "Down", "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5",
        "Numpad6", "Numpad7", "Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13",
        "F14", "F15", "Pause", "Mouse1", "Mouse2"
    };

    std::vector<std::string> InputName = {
        "ATTACK1", "ATTACK2", "UP", "LEFT", "DOWN", "RIGHT", "PRESSED", "RELEASED"
    };

    void optionKeyboard::start(sfs::Scene &scene) noexcept
    {
        _input = scene.getGameObjects<InputHandler>()[0];
        _optionMenuBox = &addComponent<sfs::Sprite>(*scene.getAssetTexture("local-assets/sprites/Menu/ui/OptionWindow.png"));
        _optionMenuBox->setScale(sf::Vector2f(1.5, 1));
		addComponent<PadderW<optionKeyboard>>(0, *this);
		addComponent<PadderH<optionKeyboard>>(0, *this);
        auto text = &addComponent<sfs::Text>(*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), "key mapping", sf::Color::White, 35);
        auto posX = (_optionMenuBox->getGlobalBounds().width / 2) - (text->getGlobalBounds().width / 2);
        text->setOffset(sf::Vector2f(posX, 10));
        auto posY = 50;

        for (int i = 0; i != 6; i ++) {

            auto button = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
												*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
												std::bind(&optionKeyboard::changeBinding, this, (UdpPrctl::inputType)i), InputName[i], sf::Color::White, 20);
		    button->setScale(sf::Vector2f(0.7, 0.5));
            text = &addComponent<sfs::Text>(*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), InputName[i], sf::Color::White, 20);
            if (i % 2 == 1) {
                posX = _optionMenuBox->getPosition().x + _optionMenuBox->getGlobalBounds().width - 25 - button->getGlobalBounds().width;
            } else {
                posX = _optionMenuBox->getPosition().x + 25;
                posY += 75;
            }
            auto textPosX = posX;
            button->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(posX, posY));
            text->setOffset(sf::Vector2f(textPosX + 10, posY - 25));
            _buttons.push_back(std::make_pair(button, text));
        }
        auto defaultButton = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
					    					*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
											std::bind(&optionKeyboard::setDefaultBindings, this), "default keys", sf::Color::White, 20);
        defaultButton->setScale(sf::Vector2f(0.8, 0.6));
        posX = (_optionMenuBox->getGlobalBounds().width / 2) - (defaultButton->getGlobalBounds().width / 2);
        defaultButton->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(posX, posY + 75));

        auto closeButton = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
					    				    *scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
											std::bind(&optionKeyboard::closeOptions, this), "resume", sf::Color::White, 20);
        closeButton->setScale(sf::Vector2f(0.7, 0.5));
        posX = (_optionMenuBox->getGlobalBounds().width / 2) - (closeButton->getGlobalBounds().width / 2);
        posY = _optionMenuBox->getGlobalBounds().height + 10;
        closeButton->addComponent<sfs::Offset>(this->getPosition(), sf::Vector2f(posX, posY));
        //closeButton->addComponent<PadderH<sfs::Button>>(120, *closeButton);
    }

    void optionKeyboard::update(sfs::Scene &) noexcept
    {
        std::string letter = "Unknow";
        bool waiting = false;
        
        auto matrix = _input->getMatrix()[sf::Event::KeyPressed];
        for (int i = 0; i != 6; i += 1) {
            waiting = false;
            if (_buttons[i].first->getString() == "waiting..." && _input->getKeyboardActive() == true) {
                waiting = true;
            }
            for (size_t j = 0; j < matrix.size(); j += 1) {
                if ((int)matrix[j] == i) {
                    letter = keys[j];
                    break ;
                } else
                    letter = "Unknow";
            }
            if (waiting == false)
                _buttons[i].first->setString(letter);
            else
                _buttons[i].first->setString("waiting...");
        }
    }

    void optionKeyboard::changeBinding(UdpPrctl::inputType type) noexcept
    {
        for (auto &i : _buttons)
            if (i.first->getString() == "waiting...")
                return;
        _buttons[(int)type].first->setString("waiting...");
		_input->changeKeyDetection(true, type);
    }

    void optionKeyboard::setDefaultBindings() noexcept
    {
        _input->setDefaultKeys();
    }
}