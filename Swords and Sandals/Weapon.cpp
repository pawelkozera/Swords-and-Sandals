#include "Weapon.h"

Weapon::Weapon(const sf::Texture& texture, int attack, int price, std::string name, std::string type) : Object(texture), Item(name, price) {
    this->attack = attack;
    this->type = type;
}

const bool Weapon::isClicked(const sf::Vector2f& mousePosition) const {
    sf::FloatRect buttonBounds = getSprite().getGlobalBounds();

    if (buttonBounds.contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }

    return false;
}

const int Weapon::getAttack() const
{
    return attack;
}

const std::string Weapon::getType() const
{
    return type;
}
