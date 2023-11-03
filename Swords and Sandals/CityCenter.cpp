#include "CityCenter.h"

CityCenter::CityCenter()
{
}

CityCenter::CityCenter(sf::Texture &cityTexture, std::unordered_map<std::string, Button> &buttons) : buttons(buttons) {
	citySprite.setTexture(cityTexture);
	citySprite.setPosition(0.0f, -30.0f);
}

const sf::Sprite CityCenter::getSprite() const {
	return citySprite;
}

void CityCenter::displayButtons(sf::RenderWindow &window) {
    for (const auto& pair : buttons) {
        const Button& button = pair.second;
        window.draw(button.getSprite());
    }
}

void CityCenter::displayCity(sf::RenderWindow& window) {
    window.draw(citySprite);
}

void CityCenter::setUpPositionOfButtons() {
    if (buttons.find("arena") != buttons.end()) {
        buttons.at("arena").setPosition(sf::Vector2f(434.0f, 290.0f));
    }
    if (buttons.find("armorer") != buttons.end()) {
        buttons.at("armorer").setPosition(sf::Vector2f(600.0f, 680.0f));
    }
    if (buttons.find("weaponsmith") != buttons.end()) {
        buttons.at("weaponsmith").setPosition(sf::Vector2f(250.0f, 680.0f));
    }
}

const Button CityCenter::getButton(const std::string& buttonName) const {
    if (buttons.find(buttonName) != buttons.end()) {
        return buttons.at(buttonName);
    }

    return Button();
}
