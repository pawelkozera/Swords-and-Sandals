#include "CityCenter.h"

CityCenter::CityCenter()
{
}

CityCenter::CityCenter(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(cityTexture, buttons) {
    setPosition(sf::Vector2f(0.0f, -30.0f));
}

void CityCenter::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button> &buttons = getButtons();

    if (buttons.find("arena") != buttons.end()) {
        buttons.at("arena").setPosition(sf::Vector2f(434.0f, 290.0f));
    }
    if (buttons.find("armorer") != buttons.end()) {
        buttons.at("armorer").setPosition(sf::Vector2f(600.0f, 680.0f));
    }
    if (buttons.find("weaponsmith") != buttons.end()) {
        buttons.at("weaponsmith").setPosition(sf::Vector2f(250.0f, 680.0f));
    }
    if (buttons.find("characterCreation") != buttons.end()) {
        buttons.at("characterCreation").setPosition(sf::Vector2f(860.0f, 840.0f));
    }
}