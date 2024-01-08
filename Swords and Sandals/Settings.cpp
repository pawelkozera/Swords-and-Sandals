#include "Settings.h"

Settings::Settings()
{
}

Settings::Settings(sf::Texture& backgroundTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(backgroundTexture, buttons) {
    volume = 0.0;
}

void Settings::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find("plusVolume") != buttons.end()) {
        buttons.at("plusVolume").setPosition(sf::Vector2f(580.0f, 200.0f));
    }

    if (buttons.find("minusVolume") != buttons.end()) {
        buttons.at("minusVolume").setPosition(sf::Vector2f(300.0f, 200.0f));
    }
    
    if (buttons.find("backButton") != buttons.end()) {
        buttons.at("backButton").setPosition(sf::Vector2f(100.0f, 750.0f));
    }
}

void Settings::displayInterface(sf::RenderWindow& window) {
    sf::RectangleShape background(sf::Vector2f(window.getSize().x - 40, window.getSize().y - 300));
    background.setFillColor(sf::Color(148, 75, 34, 200));
    background.setPosition(20, 60);
    window.draw(background);

    sf::Font font;
    if (!font.loadFromFile("Fonts/PlayfairDisplay.ttf")) {}

    sf::Text stats;
    stats.setFont(font);
    stats.setCharacterSize(30);
    stats.setFillColor(sf::Color::White);

    stats.setString("Volume: " + std::to_string(volume));
    stats.setPosition(400, 210);
    window.draw(stats);
}

void Settings::checkForClickedButton(const sf::Vector2f& mousePosition, GameState& gameState) {
    for (auto& pair : getButtons()) {
        const std::string& buttonName = pair.first;
        Button& button = pair.second;

        if (button.isClicked(mousePosition)) {
            handleButtonClick(buttonName, gameState);
            break;
        }
    }
}

void Settings::handleButtonClick(const std::string& buttonName, GameState &gameState) {
    if (buttonName.find("plusVolume") != std::string::npos) {
        if (volume < 100) {
            volume += 10;
        }
    }
    else if (buttonName.find("minusVolume") != std::string::npos) {
        if (volume > 0) {
            volume -= 10;
        }
    }

    if (buttonName == "backButton") {
        gameState.setMode(GameState::GameMode::MainMenu);
    }
}