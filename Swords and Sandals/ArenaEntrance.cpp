#include "ArenaEntrance.h"

ArenaEntrance::ArenaEntrance()
{
}

ArenaEntrance::ArenaEntrance(sf::Texture& backgroundTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(backgroundTexture, buttons) {
}

void ArenaEntrance::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find("goToCity") != buttons.end()) {
        buttons.at("goToCity").setPosition(sf::Vector2f(100.0f, 800.0f));
    }

    if (buttons.find("fight") != buttons.end()) {
        buttons.at("fight").setPosition(sf::Vector2f(444.0f, 600.0f));
    }
}

void ArenaEntrance::checkForClickedButton(const sf::Vector2f& mousePosition, GameState& gameState, Player& player, Character& enemy, Arena& arena) {
    for (auto& pair : getButtons()) {
        const std::string& buttonName = pair.first;
        Button& button = pair.second;

        if (button.isClicked(mousePosition)) {
            handleButtonClick(buttonName, gameState, player, enemy, arena);
            break;
        }
    }
}

void ArenaEntrance::handleButtonClick(const std::string& buttonName, GameState& gameState, Player& player, Character& enemy, Arena& arena) {
    if (buttonName.find("goToCity") != std::string::npos) {
        gameState.setMode(GameState::GameMode::InCity);
    }
    else if (buttonName.find("fight") != std::string::npos) {
        gameState.setMode(GameState::GameMode::InArena);
        player.setBodyPosition(sf::Vector2f(100, 630));
        enemy.setBodyPosition(sf::Vector2f(920, 630));
        arena.setUpPositionOfButtons(player);
    }
}

void ArenaEntrance::displayInterface(sf::RenderWindow& window, Player& player, Character& enemy) {
    sf::RectangleShape backgroundPlayer(sf::Vector2f(window.getSize().x/2 - 160, window.getSize().y - 240));
    backgroundPlayer.setFillColor(sf::Color(148, 75, 34, 200));
    backgroundPlayer.setPosition(20, 60);
    window.draw(backgroundPlayer);

    sf::RectangleShape backgroundEnemy(sf::Vector2f(window.getSize().x/2 - 160, window.getSize().y - 240));
    backgroundEnemy.setFillColor(sf::Color(148, 75, 34, 200));
    backgroundEnemy.setPosition(window.getSize().x / 2 + 130, 60);
    window.draw(backgroundEnemy);

    sf::Font font;
    if (!font.loadFromFile("Fonts/PlayfairDisplay.ttf")) {}

    sf::Text stats;
    stats.setFont(font);
    stats.setCharacterSize(20);
    stats.setFillColor(sf::Color::White);

    float baseXposition = 80.0f;
    float baseYposition = 420.0f;
    float paddingY = 30.0f;
    float paddingX = 140.0f;

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

    player.setBodyPosition(sf::Vector2f(160, 180));
    player.display(window);

    enemy.setBodyPosition(sf::Vector2f(780, 180));
    enemy.display(window);

    stats.setString("Opponent");
    stats.setCharacterSize(30);
    stats.setPosition(740.0f, 80.0f);
    window.draw(stats);
    stats.setCharacterSize(20);

    baseXposition = 700.0f;
    baseYposition = 420.0f;
    paddingY = 30.0f;
    paddingX = 140.0f;

    drawStat("Strength", (enemy.getStrength() < 3) ? "Very Weak" :
        (enemy.getStrength() < 5) ? "Weak" :
        (enemy.getStrength() < 8) ? "Moderate" :
        "Strong");

    drawStat("Agility", (enemy.getAgility() < 3) ? "Very Low" :
        (enemy.getAgility() < 5) ? "Low" :
        (enemy.getAgility() < 8) ? "Moderate" :
        "High");

    drawStat("Vitality", (enemy.getVitality() < 3) ? "Very Low" :
        (enemy.getVitality() < 5) ? "Low" :
        (enemy.getVitality() < 8) ? "Moderate" :
        "High");

    drawStat("Stamina", (enemy.getStamina() < 3) ? "Very Low" :
        (enemy.getStamina() < 5) ? "Low" :
        (enemy.getStamina() < 8) ? "Moderate" :
        "High");

    drawStat("Attack", (enemy.getAttack() < 3) ? "Very Weak" :
        (enemy.getAttack() < 5) ? "Weak" :
        (enemy.getAttack() < 8) ? "Moderate" :
        "Strong");

    drawStat("Defence", (enemy.getDefence() < 3) ? "Very Weak" :
        (enemy.getDefence() < 5) ? "Weak" :
        (enemy.getDefence() < 8) ? "Moderate" :
        "Strong");

    drawStat("Charisma", (enemy.getCharisma() < 3) ? "Very Low" :
        (enemy.getCharisma() < 5) ? "Low" :
        (enemy.getCharisma() < 8) ? "Moderate" :
        "High");
}