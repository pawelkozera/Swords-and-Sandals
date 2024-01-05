#include "Settings.h"

Settings::Settings()
{
}

Settings::Settings(sf::Texture& backgroundTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(backgroundTexture, buttons) {
}

void Settings::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find("") != buttons.end()) {
        buttons.at("").setPosition(sf::Vector2f(100.0f, 800.0f));
    }
}