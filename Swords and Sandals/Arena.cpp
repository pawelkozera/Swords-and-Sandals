#include "Arena.h"

Arena::Arena()
{
}

Arena::Arena(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(cityTexture, buttons) {
}

void Arena::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find("movePlayer") != buttons.end()) {
        buttons.at("movePlayer").setPosition(sf::Vector2f(400.0f, 420.0f));
    }
}

void Arena::checkForClickedButton(const sf::Vector2f& mousePosition, Player& player) {
    for (auto& pair : getButtons()) {
        const std::string& buttonName = pair.first;
        Button& button = pair.second;

        if (button.isClicked(mousePosition)) {
            handleButtonClick(buttonName, player);
            break;
        }
    }
}

void Arena::handleButtonClick(const std::string& buttonName, Player& player) {
    if (buttonName.find("movePlayerForward") != std::string::npos) {
        player.moveBody(sf::Vector2f(10, 0));
    }
}