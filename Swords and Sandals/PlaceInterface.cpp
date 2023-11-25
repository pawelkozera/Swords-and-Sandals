#include "PlaceInterface.h"

PlaceInterface::PlaceInterface() : areButtonsHidden(true)
{
}

PlaceInterface::PlaceInterface(sf::Texture& texture, std::unordered_map<std::string, Button>& buttons) : buttons(buttons) {
    sprite.setTexture(texture);
}

const sf::Sprite PlaceInterface::getSprite() const {
    return sprite;
}

void PlaceInterface::setPosition(const sf::Vector2f position) {
    sprite.setPosition(position);
}

void PlaceInterface::displayButtons(sf::RenderWindow& window) {
    for (const auto& pair : buttons) {
        const Button& button = pair.second;
        window.draw(button.getSprite());
    }
}

void PlaceInterface::setUpPositionOfButtons(){}

void PlaceInterface::hideButtons() {
    for (auto& pair : buttons) {
        Button& button = pair.second;
        button.setPosition(sf::Vector2f(-100.0f, -100.0f));
    }

    areButtonsHidden = true;
}

void PlaceInterface::displayBackground(sf::RenderWindow& window) {
    window.draw(sprite);
}

Button PlaceInterface::getButton(const std::string& buttonName) {
    if (buttons.find(buttonName) != buttons.end()) {
        return buttons.at(buttonName);
    }

    return Button();
}

std::unordered_map<std::string, Button>& PlaceInterface::getButtons() {
    return buttons;
}

void PlaceInterface::setSpriteTexture(sf::Texture &texture) {
    sprite.setTexture(texture);
}

const bool PlaceInterface::getAreButtonsHidden()
{
    return areButtonsHidden;
}

void PlaceInterface::setButtonsHidden(bool buttonsHidden) {
    areButtonsHidden = buttonsHidden;
}
