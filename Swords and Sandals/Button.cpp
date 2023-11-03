#include "Button.h"

Button::Button() {}

Button::Button(const sf::Texture &texture) : Object(texture) {
	setScale(1.0f, 1.0f);
}

const bool Button::isClicked(const sf::Vector2f& mousePosition) const {
    sf::FloatRect buttonBounds = getSprite().getGlobalBounds();

    if (buttonBounds.contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }

    return false;
}