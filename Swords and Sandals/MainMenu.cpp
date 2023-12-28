#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(sf::Texture& backgroundTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(backgroundTexture, buttons) {
}

void MainMenu::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();
    
    if (buttons.find("mainMenuLogo") != buttons.end()) {
        buttons.at("mainMenuLogo").setPosition(sf::Vector2f(20.0f, 80.0f));
    }

    if (buttons.find("continue") != buttons.end()) {
        buttons.at("continue").setPosition(sf::Vector2f(100.0f, 400.0f));
    }

    if (buttons.find("newGame") != buttons.end()) {
        buttons.at("newGame").setPosition(sf::Vector2f(100.0f, 500.0f));
    }

    if (buttons.find("loadGame") != buttons.end()) {
        buttons.at("loadGame").setPosition(sf::Vector2f(100.0f, 600.0f));
    }

    if (buttons.find("settings") != buttons.end()) {
        buttons.at("settings").setPosition(sf::Vector2f(100.0f, 700.0f));
    }

    if (buttons.find("quit") != buttons.end()) {
        buttons.at("quit").setPosition(sf::Vector2f(100.0f, 800.0f));
    }
}