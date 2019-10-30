#include "Utils.hpp"

namespace cf
{
    void Background::start(sfs::Scene &scene) noexcept
    {
        if (_path == "") {
            srand(time(nullptr));
            setPosition(sf::Vector2f(0, 1400));
            int choice = std::rand() % 2;
            if (choice == 0)
                _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("local-assets/sprites/Menu/optionBackgrounds/Background1.png"));
            else if (choice == 1)
                _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture("local-assets/sprites/Menu/optionBackgrounds/Background2.png"));
        } else if (_path != "")
            _image = &addComponent<sfs::Sprite>(*scene.getAssetTexture(_path));
    }

    void Background::update(sfs::Scene &) noexcept
    {
        if (_velo != nullptr && _lock == false) {
            auto pos = getPosition();
            if (pos.y <= 0) {
                pos.y = 0;
                _velo->destroy();
                _velo = nullptr;
                _lock = true;
            }
        }
    }

    sf::FloatRect Background::getGlobalBounds() noexcept
	{
		return _image->getGlobalBounds();
	}

    void Background::addVelocity(sf::Vector2f speed) noexcept
    {
        if (_velo != nullptr) {
            _velo->destroy();
            _velo = nullptr;
            _velo = &addComponent<sfs::Velocity>(speed);
        } else if (_velo == nullptr)
            _velo = &addComponent<sfs::Velocity>(speed);
    }

    Text::Text(const sf::Font &font, const std::string &name,
			  const sf::Vector2f &pos, uint32_t size) noexcept
	    : _text(nullptr)
	{
		setPosition(pos);
		_text = &addComponent<sfs::Text>(font, name, sf::Color::White, size);
	}

	void Text::setString(const std::string &str) noexcept
	{
		_text->setString(str);
	}

	sf::FloatRect Text::getGlobalBounds() noexcept
	{
		return _text->getGlobalBounds();
	}
}
