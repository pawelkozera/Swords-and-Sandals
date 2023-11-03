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
