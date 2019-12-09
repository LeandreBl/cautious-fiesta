#include "UiWeapon.hpp"
#include <Padder.hpp>

namespace cf
{
    UiWeapon::UiWeapon() noexcept
        : _weapon(nullptr)
        , _box(nullptr)
    {
    }

    void UiWeapon::start(sfs::Scene &scene) noexcept
    {
        _box = &addComponent<sfs::Sprite>(*scene.getAssetTexture("local-assets/sprites/Menu/ui/BlankButton3.png"));
	    _box->setScale(sf::Vector2f(2.5, 2.5));
        _weapon = &addComponent<sfs::Sprite>(sf::Texture());
        _weapon->setScale(sf::Vector2f(2, 2));
        addComponent<PadderR<UiWeapon>>(0, *this);
    }

    void UiWeapon::setUiWeapon(const sf::Texture &texture) noexcept
    {
        _weapon->setTexture(texture, true);
        auto posY = (_box->getGlobalBounds().height / 2) - (_weapon->getGlobalBounds().height / 2);
        auto posX = (_box->getGlobalBounds().width / 2) - (_weapon->getGlobalBounds().width / 2);
        _weapon->setOffset(sf::Vector2f(posX, posY));
    }
}