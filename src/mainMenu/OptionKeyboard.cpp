#include <Offset.hpp>
#include "Option.hpp"
#include "Udp.h"
#include "PaddedSprite.hpp"
#include "InputHandler.hpp"

namespace cf
{
    std::vector<std::string> keys = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
        "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Escape", "LControl", "LShift", "LAlt", "LSystem",
        "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket", "RBracket", "Semicolon", "Comma", "Period", "Quote", "Slash", "Backslash",
        "Tilde", "Equal", "Hyphen", "Space", "Enter", "Backspace", "Tab", "PageUp", "PageDown", "End", "Home", "Insert", "Delete", "Add",
        "Subtract", "Multiply", "Divide", "Left", "Right", "Up", "Down", "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5",
        "Numpad6", "Numpad7", "Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13",
        "F14", "F15", "Pause", "Mouse2", "Mouse1"
    };

    std::vector<std::string> InputName = {
        "UNKNOWN_KEY", "ATTACK1", "ATTACK2", "UP", "LEFT", "DOWN", "RIGHT", "PRESSED", "RELEASED"
    };

    void optionKeyboard::start(sfs::Scene &scene) noexcept
    {
        _optionMenuBox = &addComponent<sfs::Sprite>(*scene.getAssetTexture("local-assets/sprites/Menu/ui/OptionWindow.png"));
        _optionMenuBox->setScale(sf::Vector2f(1.5, 1));
		addComponent<PadderW<optionKeyboard>>(0, *this);
		addComponent<PadderH<optionKeyboard>>(0, *this);
        auto text = &addComponent<sfs::Text>(*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), "key mapping", sf::Color::White, 35);
        auto posX = (_optionMenuBox->getGlobalBounds().width / 2) - (text->getGlobalBounds().width / 2);
        text->setOffset(sf::Vector2f(posX, 10));
        auto posY = 50;

        auto input = scene.getGameObjects<InputHandler>()[0]->getMatrix();

        for (int i = 0; i != 6; i ++) {
            std::string letter = "letter";

            for (auto &matrix : input) { //TODO a mettre dans le update
                for (size_t j = 0; j < matrix.size(); j += 1)
                    if ((int)matrix[j] == i) {
                        letter = keys[j];
                        if (i <= 1) {
                            if ((int)matrix[j] == 0)
                                letter = keys[keys.size() - 1];
                            else
                                letter = keys[keys.size() - 2];
                        }
                    }
            }

            auto button = &addChild<sfs::Button>(scene, *scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton2.png"),
												*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), sf::Vector2f(-1000, -1000),
												std::bind(&optionKeyboard::changeBinding, this, std::ref(scene)), letter, sf::Color::White, 20);
		    button->setScale(sf::Vector2f(0.7, 0.5));
            text = &addComponent<sfs::Text>(*scene.getAssetFont("local-assets/fonts/commodore-64.ttf"), InputName[i + 1], sf::Color::White, 20);
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
    }

    void optionKeyboard::changeBinding(sfs::Scene &scene) noexcept
    {
		//scene.getGameObjects<InputHandler>()[0]->changeKeyDetection(true);
    }
}