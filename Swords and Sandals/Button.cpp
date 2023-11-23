#include "Button.h"

Button::Button() {}

Button::Button(const sf::Texture &texture) : Object(texture) {
	setScale(1.0f, 1.0f);
}

const bool Button::isClicked(const sf::Vector2f& mousePosition) const {
    static bool wasMousePressed = false;
    static sf::Clock clickCooldown;

    sf::FloatRect buttonBounds = getSprite().getGlobalBounds();

    if (buttonBounds.contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!wasMousePressed && clickCooldown.getElapsedTime().asMilliseconds() > 300) {
            wasMousePressed = true;
            clickCooldown.restart();
            return true;
        }
    }
    else {
        wasMousePressed = false;
    }

    return false;
}