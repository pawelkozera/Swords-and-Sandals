#include "ArmorPiece.h"


ArmorPiece::ArmorPiece(const sf::Texture& texture) : Object(texture) {
}

const bool ArmorPiece::isClicked(const sf::Vector2f& mousePosition) const {
    sf::FloatRect buttonBounds = getSprite().getGlobalBounds();

    if (buttonBounds.contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }

    return false;
}