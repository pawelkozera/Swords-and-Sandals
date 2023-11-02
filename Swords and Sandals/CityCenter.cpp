#include "CityCenter.h"

CityCenter::CityCenter(sf::Texture &cityTexture, std::unordered_map<std::string, Button> &Buttons) : Buttons(Buttons) {
	citySprite.setTexture(cityTexture);
	citySprite.setPosition(0.0f, -30.0f);
}

const sf::Sprite CityCenter::getSprite() const {
	return citySprite;
}

void CityCenter::displayButtons(sf::RenderWindow &window) {
    for (const auto& pair : Buttons) {
        const Button& button = pair.second;
        sf::Sprite sprite = button.getSprite();
        sprite.setPosition(button.getPosition());
        window.draw(sprite);
    }
}

void CityCenter::displayCity(sf::RenderWindow& window) {
    window.draw(citySprite);
}

void CityCenter::setUpPositionOfButtons() {
    if (Buttons.find("arena") != Buttons.end()) {
        Buttons.at("arena").setPosition(sf::Vector2f(434.0f, 290.0f));
    }
    if (Buttons.find("armorer") != Buttons.end()) {
        Buttons.at("armorer").setPosition(sf::Vector2f(600.0f, 680.0f));
    }
    if (Buttons.find("weaponsmith") != Buttons.end()) {
        Buttons.at("weaponsmith").setPosition(sf::Vector2f(250.0f, 680.0f));
    }
}
