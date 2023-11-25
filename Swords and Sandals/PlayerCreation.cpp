#include "PlayerCreation.h"

PlayerCreation::PlayerCreation()
{
}

PlayerCreation::PlayerCreation(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(cityTexture, buttons) {
    setPosition(sf::Vector2f(0.0f, -30.0f));

    oldAgility = oldAttack = oldCharisma = oldDefence = oldStamina = oldStrength = oldVitality = 1;
}

void PlayerCreation::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find("goToCityButton") != buttons.end()) {
        buttons.at("goToCityButton").setPosition(sf::Vector2f(700.0f , 720.0f));
    }

    float baseXposition = 40.0f;
    float baseYposition = 70.0f;
    float paddingY = 86.0f;
    float paddingX = 220.0f;

    auto setButtonPosition = [&](const std::string& buttonName) {
        if (buttons.find(buttonName) != buttons.end()) {
            if (buttonName.find("plus") != std::string::npos) {
                buttons.at(buttonName).setPosition(sf::Vector2f(baseXposition + paddingX, baseYposition));
                baseYposition += paddingY;
            }
            else {
                buttons.at(buttonName).setPosition(sf::Vector2f(baseXposition, baseYposition));
            }
        }
        };

    setButtonPosition("minusStrengthButton");
    setButtonPosition("plusStrengthButton");
    setButtonPosition("minusAgilityButton");
    setButtonPosition("plusAgilityButton");
    setButtonPosition("minusVitalityButton");
    setButtonPosition("plusVitalityButton");
    setButtonPosition("minusStaminaButton");
    setButtonPosition("plusStaminaButton");
    setButtonPosition("minusAttackButton");
    setButtonPosition("plusAttackButton");
    setButtonPosition("minusDefenceButton");
    setButtonPosition("plusDefenceButton");
    setButtonPosition("minusCharismaButton");
    setButtonPosition("plusCharismaButton");
}

void PlayerCreation::displayInterface(sf::RenderWindow& window, Player& player) {
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

    stats.setString("Available points:");
    stats.setPosition(600, 600);
    window.draw(stats);

    stats.setString(std::to_string(player.getAvailablePoints()));
    stats.setPosition(840, 596);
    window.draw(stats);

    float baseXposition = 120.0f;
    float baseYposition = 80.0f;
    float paddingY = 85.0f;
    float paddingX = 240.0f;

    auto drawStat = [&](const std::string& label, const std::string& value) {
        stats.setString(label);
        stats.setPosition(baseXposition, baseYposition);
        window.draw(stats);

        stats.setString(value);
        stats.setPosition(baseXposition + paddingX, baseYposition);
        baseYposition += paddingY;
        window.draw(stats);
        };

    drawStat("Strength", (player.getStrength() < 3) ? "Very Weak" :
        (player.getStrength() < 5) ? "Weak" :
        (player.getStrength() < 8) ? "Moderate" :
        "Strong");

    drawStat("Agility", (player.getAgility() < 3) ? "Very Low" :
        (player.getAgility() < 5) ? "Low" :
        (player.getAgility() < 8) ? "Moderate" :
        "High");

    drawStat("Vitality", (player.getVitality() < 3) ? "Very Low" :
        (player.getVitality() < 5) ? "Low" :
        (player.getVitality() < 8) ? "Moderate" :
        "High");

    drawStat("Stamina", (player.getStamina() < 3) ? "Very Low" :
        (player.getStamina() < 5) ? "Low" :
        (player.getStamina() < 8) ? "Moderate" :
        "High");

    drawStat("Attack", (player.getAttack() < 3) ? "Very Weak" :
        (player.getAttack() < 5) ? "Weak" :
        (player.getAttack() < 8) ? "Moderate" :
        "Strong");

    drawStat("Defence", (player.getDefence() < 3) ? "Very Weak" :
        (player.getDefence() < 5) ? "Weak" :
        (player.getDefence() < 8) ? "Moderate" :
        "Strong");

    drawStat("Charisma", (player.getCharisma() < 3) ? "Very Low" :
        (player.getCharisma() < 5) ? "Low" :
        (player.getCharisma() < 8) ? "Moderate" :
        "High");
}

void PlayerCreation::checkForClickedButton(const sf::Vector2f& mousePosition, Player& player, GameState& gameState) {
    for (auto& pair : getButtons()) {
        const std::string& buttonName = pair.first;
        Button& button = pair.second;

        if (button.isClicked(mousePosition)) {
            handleButtonClick(buttonName, player, gameState);
            break;
        }
    }
}

void PlayerCreation::handleButtonClick(const std::string& buttonName, Player& player, GameState& gameState) {
    if (buttonName.find("plus") != std::string::npos && player.getAvailablePoints() > 0) {
        handlePlusButtonClick(buttonName, player);
    }
    else if (buttonName.find("minus") != std::string::npos) {
        handleMinusButtonClick(buttonName, player);
    }

    if (buttonName == "goToCityButton") {
        gameState.setMode(GameState::GameMode::InCity);
        setOldStats(player);

    }
}

void PlayerCreation::setOldStats(Player& player) {
    oldStrength = player.getStrength();
    oldAgility = player.getAgility();
    oldAttack = player.getAttack();
    oldCharisma = player.getCharisma();
    oldDefence = player.getDefence();
    oldStamina = player.getStamina();
    oldVitality = player.getVitality();
}

void PlayerCreation::handlePlusButtonClick(const std::string& buttonName, Player& player) {
    if (buttonName == "plusStrengthButton") {
        player.incrementStrength();
        player.addAvailablePoints(-1);
    }
    else if (buttonName == "plusAgilityButton") {
        player.incrementAgility();
        player.addAvailablePoints(-1);
    }
    else if (buttonName == "plusVitalityButton") {
        player.incrementVitality();
        player.addAvailablePoints(-1);
    }
    else if (buttonName == "plusStaminaButton") {
        player.incrementStamina();
        player.addAvailablePoints(-1);
    }
    else if (buttonName == "plusAttackButton") {
        player.incrementAttack();
        player.addAvailablePoints(-1);
    }
    else if (buttonName == "plusDefenceButton") {
        player.incrementDefence();
        player.addAvailablePoints(-1);
    }
    else if (buttonName == "plusCharismaButton") {
        player.incrementCharisma();
        player.addAvailablePoints(-1);
    }
}

void PlayerCreation::handleMinusButtonClick(const std::string& buttonName, Player& player) {
    if (buttonName == "minusStrengthButton" && player.getStrength() > oldStrength) {
        player.decrementStrength();
        player.addAvailablePoints(1);
    }
    else if (buttonName == "minusAgilityButton" && player.getAgility() > oldAgility) {
        player.decrementAgility();
        player.addAvailablePoints(1);
    }
    else if (buttonName == "minusVitalityButton" && player.getVitality() > oldVitality) {
        player.decrementVitality();
        player.addAvailablePoints(1);
    }
    else if (buttonName == "minusStaminaButton" && player.getStamina() > oldStamina) {
        player.decrementStamina();
        player.addAvailablePoints(1);
    }
    else if (buttonName == "minusAttackButton" && player.getAttack() > oldAttack) {
        player.decrementAttack();
        player.addAvailablePoints(1);
    }
    else if (buttonName == "minusDefenceButton" && player.getDefence() > oldDefence) {
        player.decrementDefence();
        player.addAvailablePoints(1);
    }
    else if (buttonName == "minusCharismaButton" && player.getCharisma() > oldCharisma) {
        player.decrementCharisma();
        player.addAvailablePoints(1);
    }
}

