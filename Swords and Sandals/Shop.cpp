#include "Shop.h"

Shop::Shop(sf::Texture& armorer, sf::Texture& weaponsmith, std::unordered_map<std::string, Button> buttons) : PlaceInterface(armorer, buttons) {
    isArmorer = true;
    this->armorer = armorer;
    this->weaponsmith = weaponsmith;
}

Shop::Shop(){
    isArmorer = true;
}

void Shop::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find("backButton") != buttons.end()) {
        buttons.at("backButton").setPosition(sf::Vector2f(100.0f, 800.0f));
    }

    setUpPositionOfButtonsArmorer(buttons);
    setUpPositionOfButtonsWeaponsmith(buttons);
}

void Shop::setUpPositionOfButtonsArmorer(std::unordered_map<std::string, Button>& buttons) {
    std::unordered_map<std::string, sf::Vector2f> buttonPositions = {
        {"helmetButton", sf::Vector2f(40.0f, 580.0f)},
        {"chestButton", sf::Vector2f(120.0f, 580.0f)},
        {"shoulderButton", sf::Vector2f(200.0f, 580.0f)},
        {"forearmButton", sf::Vector2f(280.0f, 580.0f)},
        {"armButton", sf::Vector2f(360.0f, 580.0f)},
        {"pantsButton", sf::Vector2f(440.0f, 580.0f)},
        {"thighButton", sf::Vector2f(520.0f, 580.0f)},
        {"calfButton", sf::Vector2f(600.0f, 580.0f)},
        {"feetButton", sf::Vector2f(680.0f, 580.0f)}
    };

    for (const auto& pair : buttons) {
        const std::string& buttonName = pair.first;
        if (buttonPositions.find(buttonName) != buttonPositions.end()) {
            buttons.at(buttonName).setPosition(buttonPositions.at(buttonName));
        }
    }
}

void Shop::setUpPositionOfButtonsWeaponsmith(std::unordered_map<std::string, Button>& buttons) {
}

void Shop::setShopToArmorer(bool isArmorer) {
    this->isArmorer = isArmorer;
    
    if (isArmorer) {
        setSpriteTexture(armorer);
    }
    else {
        setSpriteTexture(weaponsmith);
    }
}

void Shop::displayInterface(sf::RenderWindow& window) {
    sf::RectangleShape itemsDisplay(sf::Vector2f(630, 460));
    itemsDisplay.setFillColor(sf::Color(148, 75, 34, 200));
    itemsDisplay.setPosition(20, 60);

    sf::RectangleShape stats(sf::Vector2f(320, 460));
    stats.setFillColor(sf::Color(148, 75, 34, 200));
    stats.setPosition(680, 60);

    sf::RectangleShape iconsBackground(sf::Vector2f(980, 120));
    iconsBackground.setFillColor(sf::Color(148, 75, 34, 200));
    iconsBackground.setPosition(20, 560);

    window.draw(itemsDisplay);
    window.draw(stats);
    window.draw(iconsBackground);
}

void Shop::displayButtons(sf::RenderWindow& window) {
    std::unordered_map<std::string, Button> buttons = getButtons();
    std::vector<std::string> buttonsToDisplay;

    if (isArmorer) {
        buttonsToDisplay = {
            "backButton", "armButton", "calfButton", "chestButton", "feetButton",
            "forearmButton", "helmetButton", "pantsButton", "shoulderButton", "thighButton"
        };
    }
    else {
        buttonsToDisplay = {"backButton", "swordButton"};
    }

    for (const auto& buttonName : buttonsToDisplay) {
        if (buttons.find(buttonName) != buttons.end()) {
            const Button& button = buttons.at(buttonName);
            window.draw(button.getSprite());
        }
    }
}
