#include "ArmorPiece.h"


ArmorPiece::ArmorPiece(const sf::Texture& texture, int defence, int price, std::string name, std::string type) : Object(texture), Item(name, price) {
    this->defence = defence;
    this->type = type;
}

const bool ArmorPiece::isClicked(const sf::Vector2f& mousePosition) const {
    sf::FloatRect buttonBounds = getSprite().getGlobalBounds();

    if (buttonBounds.contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }

    return false;
}

const int ArmorPiece::getDefence() const
{
    return defence;
}

const std::string ArmorPiece::getType() const
{
    return type;
}
