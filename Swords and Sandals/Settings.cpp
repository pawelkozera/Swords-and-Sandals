#include "Settings.h"

Settings::Settings()
{
}

Settings::Settings(sf::Texture& backgroundTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(backgroundTexture, buttons) {
    volume = 0;
}

void Settings::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find("plusVolume") != buttons.end()) {
        buttons.at("plusVolume").setPosition(sf::Vector2f(400.0f, 200.0f));
    }

    if (buttons.find("minusVolume") != buttons.end()) {
        buttons.at("minusVolume").setPosition(sf::Vector2f(500.0f, 200.0f));
    }
    
    if (buttons.find("backButton") != buttons.end()) {
        buttons.at("backButton").setPosition(sf::Vector2f(100.0f, 750.0f));
    }
}