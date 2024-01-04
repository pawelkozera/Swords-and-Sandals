#include "PlayerInterface.h"

PlayerInterface::PlayerInterface() {
}

PlayerInterface::PlayerInterface(sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setScale(0.12f, 0.12f);
}

void PlayerInterface::displayInterface(sf::RenderWindow& window, Player& player) {
    sf::Vector2u windowSize = window.getSize();

    sprite.setPosition(sf::Vector2f(20, windowSize.y - 65));

    sf::RectangleShape backGround(sf::Vector2f(windowSize.x, 70));
    backGround.setFillColor(sf::Color(148, 75, 34, 255));
    backGround.setPosition(0, windowSize.y - 70);

    window.draw(backGround);
    window.draw(sprite);

    sf::Font font;
    if (!font.loadFromFile("Fonts/PlayfairDisplay.ttf")) {
    }

    sf::Text stats;
    stats.setFont(font);
    stats.setString(std::to_string(player.getGold()));
    stats.setCharacterSize(40);
    stats.setFillColor(sf::Color::White);
    stats.setPosition(sprite.getPosition().x + 80, sprite.getPosition().y);
    window.draw(stats);

    stats.setCharacterSize(34);
    stats.setString("HP");
    stats.setPosition(sprite.getPosition().x + 220, sprite.getPosition().y + 8);
    window.draw(stats);

    stats.setCharacterSize(40);
    stats.setString(std::to_string(player.getHp()));
    stats.setPosition(sprite.getPosition().x + 280, sprite.getPosition().y);
    window.draw(stats);

    stats.setCharacterSize(34);
    stats.setString("Stamina");
    stats.setPosition(sprite.getPosition().x + 380, sprite.getPosition().y + 8);
    window.draw(stats);

    stats.setCharacterSize(40);
    stats.setString(std::to_string(player.getStaminaUsage()));
    stats.setPosition(sprite.getPosition().x + 520, sprite.getPosition().y);
    window.draw(stats);

    stats.setCharacterSize(34);
    stats.setString("Armor");
    stats.setPosition(sprite.getPosition().x + 600, sprite.getPosition().y + 8);
    window.draw(stats);

    stats.setCharacterSize(40);
    stats.setString(std::to_string(player.getArmor()));
    stats.setPosition(sprite.getPosition().x + 720, sprite.getPosition().y);
    window.draw(stats);
}
