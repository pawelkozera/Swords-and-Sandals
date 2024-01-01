#include "Arena.h"

Arena::Arena()
{
}

Arena::Arena(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(cityTexture, buttons) {
    playerTurn = true;
    fightInProgress = false;
    playerWon = false;
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

    if (buttons.find("continueButton") != buttons.end()) {
        buttons.at("continueButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
    }

    if (buttons.find("startOverButton") != buttons.end()) {
        buttons.at("startOverButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
    }
}

void Arena::setUpEndOfFightPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (playerWon) {
        if (buttons.find("continueButton") != buttons.end()) {
            buttons.at("continueButton").setPosition(sf::Vector2f(460.0f, 420.0f));
        }
    }
    else {
        if (buttons.find("startOverButton") != buttons.end()) {
            buttons.at("startOverButton").setPosition(sf::Vector2f(460.0f, 420.0f));
        }
    }
}

void Arena::checkForClickedButton(const sf::Vector2f& mousePosition, Player& player, Enemy&enemy, GameState& gameState, TextureManager& textureManager, Shop& shop) {
    for (auto& pair : getButtons()) {
        const std::string& buttonName = pair.first;
        Button& button = pair.second;

        if (button.isClicked(mousePosition)) {
            handleButtonClick(buttonName, player, enemy, gameState, textureManager, shop);
            break;
        }
    }
}

void Arena::checkForEndOfFight(Player& player, Enemy& enemy) {
    if (player.getHp() <= 0) {
        setFightInProgress(false);
        playerWon = false;
        setUpEndOfFightPositionOfButtons();
    }
    else if (enemy.getHp() <= 0) {
        setFightInProgress(false);
        playerWon = true;
        setUpEndOfFightPositionOfButtons();
    }
}

void Arena::handleButtonClick(const std::string& buttonName, Player& player, Enemy&enemy, GameState& gameState, TextureManager& textureManager, Shop& shop) {
    if (fightInProgress) {
        handleButtonClickFightInProgress(buttonName, player, enemy);
        playerTurn = false;
    }
    else {
        handleButtonClickFightEnded(buttonName, player, enemy, gameState, textureManager, shop);
    }
}

void Arena::handleButtonClickFightInProgress(const std::string& buttonName, Player& player, Enemy& enemy) {
    if (buttonName.find("movePlayerForward") != std::string::npos) {
        if (player.getStaminaUsage() >= 5) {
            if (abs(enemy.getBodyPosition().x - player.getBodyPosition().x) > player.getReach()) {
                player.moveBody(sf::Vector2f(player.getSpeed(), 0));
                setUpPositionOfButtons(player);
                player.walkAnimation();
                player.setStaminaUsage(player.getStaminaUsage() - 5);
            }
        }
        else {
            player.rest();
        }
    }
    else if (buttonName.find("movePlayerBackwards") != std::string::npos) {
        if (player.getStaminaUsage() >= 5) {
            player.moveBody(sf::Vector2f(-10, 0));
            setUpPositionOfButtons(player);
            player.walkAnimation();
            player.setStaminaUsage(player.getStaminaUsage() - 5);
        }
        else {
            player.rest();
        }
    }
    else if (buttonName.find("attackPlayer") != std::string::npos) {
        if (player.getStaminaUsage() >= 7) {
            player.attackEnemy(enemy);
            player.attackAnimation(false);
            player.setStaminaUsage(player.getStaminaUsage() - 7);
        }
        else {
            player.rest();
        }
    }
    else if (buttonName.find("restPlayer") != std::string::npos) {
        player.rest();
    }
}

void Arena::handleButtonClickFightEnded(const std::string& buttonName, Player& player, Enemy& enemy, GameState& gameState, TextureManager& textureManager, Shop& shop) {
    if (buttonName.find("continueButton") != std::string::npos) {
        gameState.setMode(GameState::GameMode::InCreationMenu);
        enemy.resetStatsAndEq();
        enemy.generateNewStatsAndEq(player, textureManager);
        generatePrize(player);
    }
    else if (buttonName.find("startOverButton") != std::string::npos) {
        gameState.setMode(GameState::GameMode::InCreationMenu);
        enemy.resetStatsAndEq();
        player.resetStatsAndEq();
        player.setGold(900);
        shop.resetBoughtItems();
    }
}

void Arena::generatePrize(Player& player) {
    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_int_distribution<int> goldDistribution(1, 5);
    int goldAmount = goldDistribution(generator) * 100;

    std::uniform_int_distribution<int> pointsDistribution(1, 2);
    int points = pointsDistribution(generator);

    player.addGold(goldAmount);
    player.addAvailablePoints(points);
}

void Arena::displayEndOfFight(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Fonts/PlayfairDisplay.ttf")) {}

    sf::Text stats;
    stats.setFont(font);
    stats.setCharacterSize(80);
    stats.setFillColor(sf::Color::White);
    if (playerWon) {
        stats.setString("You win!");
    }
    else {
        stats.setString("You lose!");
    }
    stats.setPosition(360.0f, 300.0f);
    window.draw(stats);
}

void Arena::handleEnemyMove(Character& enemy, Player& player) {
    bool playerNotInReachOfAttack = abs(enemy.getBodyPosition().x - player.getBodyPosition().x) > enemy.getReach();

    if (playerNotInReachOfAttack && enemy.getStaminaUsage() >= 5) {
        enemy.moveBody(sf::Vector2f(-enemy.getSpeed(), 0));
        enemy.walkAnimation();
        enemy.setStaminaUsage(enemy.getStaminaUsage() - 5);
    }
    else if (enemy.getStaminaUsage() >= 7) {
        enemy.attackEnemy(player);
        enemy.attackAnimation(true);
        enemy.setStaminaUsage(enemy.getStaminaUsage() - 7);
    }
    else {
        enemy.rest();
    }

    playerTurn = true;
}

const bool Arena::getPlayerTurn() {
    return playerTurn;
}

const bool Arena::getFightInProgress() {
    return fightInProgress;
}

void Arena::setFightInProgress(bool fightState) {
    fightInProgress = fightState;
}