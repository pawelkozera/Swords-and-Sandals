#include "Arena.h"

Arena::Arena()
{
}

Arena::Arena(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(cityTexture, buttons) {
}

void Arena::setUpPositionOfButtons(Player& player) {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    sf::Vector2f playerPosition = player.getBodyPosition();

    if (buttons.find("movePlayerForward") != buttons.end()) {
        buttons.at("movePlayerForward").setPosition(sf::Vector2f(playerPosition.x + 90, playerPosition.y + 120));
    }

    if (buttons.find("movePlayerBackwards") != buttons.end()) {
        buttons.at("movePlayerBackwards").setPosition(sf::Vector2f(playerPosition.x - 90, playerPosition.y + 120));
    }

    if (buttons.find("attackPlayer") != buttons.end()) {
        buttons.at("attackPlayer").setPosition(sf::Vector2f(playerPosition.x + 90, playerPosition.y + 40));
    }

    if (buttons.find("restPlayer") != buttons.end()) {
        buttons.at("restPlayer").setPosition(sf::Vector2f(playerPosition.x - 100, playerPosition.y + 40));
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
        setUpPositionOfButtons(player);
    }
}