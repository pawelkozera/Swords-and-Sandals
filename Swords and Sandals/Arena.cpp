#include "Arena.h"

Arena::Arena()
{
}

Arena::Arena(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(cityTexture, buttons) {
    playerTurn = true;
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

void Arena::checkForClickedButton(const sf::Vector2f& mousePosition, Player& player, Character &enemy) {
    for (auto& pair : getButtons()) {
        const std::string& buttonName = pair.first;
        Button& button = pair.second;

        if (button.isClicked(mousePosition)) {
            handleButtonClick(buttonName, player, enemy);
            playerTurn = false;
            break;
        }
    }
}

void Arena::handleButtonClick(const std::string& buttonName, Player& player, Character &enemy) {
    if (buttonName.find("movePlayerForward") != std::string::npos) {
        player.moveBody(sf::Vector2f(10, 0));
        setUpPositionOfButtons(player);
        player.walkAnimation();
    }
    else if (buttonName.find("movePlayerBackwards") != std::string::npos) {
        player.moveBody(sf::Vector2f(-10, 0));
        setUpPositionOfButtons(player);
        player.walkAnimation();
    }
    else if (buttonName.find("attackPlayer") != std::string::npos) {
        player.attackEnemy(enemy);
        player.attackAnimation(false);
    }
    else if (buttonName.find("restPlayer") != std::string::npos) {
        player.rest();
    }
}

void Arena::handleEnemyMove(Character& enemy, Player& player) {
    if (abs(enemy.getBodyPosition().x - player.getBodyPosition().x) > 80) {
        enemy.moveBody(sf::Vector2f(-40, 0));
        enemy.walkAnimation();
    }
    else {
        enemy.attackEnemy(player);
        enemy.attackAnimation(true);
    }
    playerTurn = true;
}

const bool Arena::getPlayerTurn() {
    return playerTurn;
}