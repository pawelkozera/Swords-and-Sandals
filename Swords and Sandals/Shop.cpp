#include "Shop.h"


Shop::Shop(std::unordered_map<std::string, Button> buttons, TextureManager& textureManager, Player* player)
    : PlaceInterface(textureManager.getTexture("armorerBackground"), buttons), player(player) {
    isArmorer = true;
    this->armorer = &textureManager.getTexture("armorerBackground");
    this->weaponsmith = &textureManager.getTexture("weaponsmithBackground");
    setMode(ShopMode::Nothing);
    selectedArmorPiece = nullptr;
    selectedWeapon = nullptr;

    availableArmorPieces.insert({ "head", ArmorPiece(textureManager.getTexture("DKAhead"), 1, 200, "Dark knight", "helmet")});
    availableArmorPieces.insert({ "chest", ArmorPiece(textureManager.getTexture("DKAchest"), 1, 500, "Dark knight", "breastplate")});

    availableArmorPieces.insert({ "shoulderLeft", ArmorPiece(textureManager.getTexture("DKAshoulder"), 1, 300, "Dark knight", "shoulderguard left")});

    ArmorPiece DKAshoulderRight(textureManager.getTexture("DKAshoulder"), 1, 300, "Dark knight", "shoulderguard right");
    DKAshoulderRight.flipSprite();
    availableArmorPieces.insert({ "shoulderRight", DKAshoulderRight });

    availableArmorPieces.insert({ "elbowLeft", ArmorPiece(textureManager.getTexture("DKAelbow"), 1, 300, "Dark knight", "gauntlet left") });

    ArmorPiece DKAeblowRight(textureManager.getTexture("DKAelbow"), 1, 300, "Dark knight", "gauntlet right");
    DKAeblowRight.flipSprite();
    availableArmorPieces.insert({ "elbowRight", DKAeblowRight });

    availableArmorPieces.insert({ "armLeft", ArmorPiece(textureManager.getTexture("DKAarm"), 1, 300, "Dark knight", "glove left")});

    ArmorPiece DKAarmRight(textureManager.getTexture("DKAarm"), 1, 300, "Dark knight", "glove right");
    DKAarmRight.flipSprite();
    availableArmorPieces.insert({ "armRight",  DKAarmRight });

    availableArmorPieces.insert({ "pelvis", ArmorPiece(textureManager.getTexture("DKApelvis"), 1, 300, "Dark knight", "pants")});

    availableArmorPieces.insert({ "thighLeft", ArmorPiece(textureManager.getTexture("DKAthigh"), 1, 300, "Dark knight", "greave left")});

    ArmorPiece DKAthighRight(textureManager.getTexture("DKAthigh"), 1, 300, "Dark knight", "greave right");
    DKAthighRight.flipSprite();
    availableArmorPieces.insert({ "thighRight",  DKAthighRight });

    availableArmorPieces.insert({ "legLeft", ArmorPiece(textureManager.getTexture("DKAleg"), 1, 300, "Dark knight", "shinguard left")});

    ArmorPiece DKAlegRight(textureManager.getTexture("DKAleg"), 1, 300, "Dark knight", "shinguard right");
    DKAlegRight.flipSprite();
    availableArmorPieces.insert({ "legRight",  DKAlegRight });

    availableArmorPieces.insert({ "footLeft", ArmorPiece(textureManager.getTexture("DKAfoot"), 1, 300, "Dark knight", "boot left")});

    ArmorPiece DKAfootRight(textureManager.getTexture("DKAfoot"), 1, 300, "Dark knight", "boot right");
    DKAfootRight.flipSprite();
    availableArmorPieces.insert({ "footRight",  DKAfootRight });

    const std::unordered_multimap<std::string, ArmorPiece>& armorMap = availableArmorPieces;

    for (const auto& armor : armorMap) {
        boughtArmorPieces.insert({ armor.second.getName() + armor.second.getType(), false});
    }

    availableWeapons.insert({ "handRight", Weapon(textureManager.getTexture("blueSword"), 1, 300, "Blue", "sword") });

    const std::unordered_multimap<std::string, Weapon>& weaponMap = availableWeapons;

    for (const auto& weapon : weaponMap) {
        boughtWeapons.insert({ weapon.second.getName() + weapon.second.getType(), false });
    }
    
    setUpItemsPosition();
}

Shop::Shop(){}

void Shop::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find("backButton") != buttons.end()) {
        buttons.at("backButton").setPosition(sf::Vector2f(100.0f, 750.0f));
    }

    if (buttons.find("buyButton") != buttons.end()) {
        buttons.at("buyButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
    }

    if (buttons.find("equipButton") != buttons.end()) {
        buttons.at("equipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
    }

    if (buttons.find("unequipButton") != buttons.end()) {
        buttons.at("unequipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
    }

    setUpPositionOfIconButtons();

    setButtonsHidden(false);
}

void Shop::setUpPositionOfIconButtons() {
    std::unordered_map<std::string, sf::Vector2f> buttonPositions;

    if (isArmorer) {
        buttonPositions = {
        {"helmetButton", sf::Vector2f(40.0f, 580.0f)},
        {"chestButton", sf::Vector2f(120.0f, 580.0f)},
        {"shoulderButton", sf::Vector2f(200.0f, 580.0f)},
        {"forearmButton", sf::Vector2f(280.0f, 580.0f)},
        {"armButton", sf::Vector2f(360.0f, 580.0f)},
        {"pantsButton", sf::Vector2f(440.0f, 580.0f)},
        {"thighButton", sf::Vector2f(520.0f, 580.0f)},
        {"calfButton", sf::Vector2f(600.0f, 580.0f)},
        {"feetButton", sf::Vector2f(680.0f, 580.0f)},
        {"swordButton", sf::Vector2f(-100.0f, -100.0f)},
        };
    }
    else {
        buttonPositions = {
        {"swordButton", sf::Vector2f(40.0f, 580.0f)},
        {"helmetButton", sf::Vector2f(-100.0f, -100.0f)},
        {"chestButton", sf::Vector2f(-100.0f, -100.0f)},
        {"shoulderButton", sf::Vector2f(-100.0f, -100.0f)},
        {"forearmButton", sf::Vector2f(-100.0f, -100.0f)},
        {"armButton", sf::Vector2f(-100.0f, -100.0f)},
        {"pantsButton", sf::Vector2f(-100.0f, -100.0f)},
        {"thighButton", sf::Vector2f(-100.0f, -100.0f)},
        {"calfButton", sf::Vector2f(-100.0f, -100.0f)},
        {"feetButton", sf::Vector2f(-100.0f, -100.0f)}
        };
    }

    std::unordered_map<std::string, Button>& buttons = getButtons();

    for (const auto& pair : buttons) {
        const std::string& buttonName = pair.first;
        if (buttonPositions.find(buttonName) != buttonPositions.end()) {
            buttons.at(buttonName).setPosition(buttonPositions.at(buttonName));
        }
    }
}

void Shop::setShopToArmorer(bool isArmorer) {
    this->isArmorer = isArmorer;
    
    if (isArmorer) {
        setSpriteTexture(*armorer);
    }
    else {
        setSpriteTexture(*weaponsmith);
    }
}

void Shop::displayInterface(sf::RenderWindow& window) {
    sf::RectangleShape itemsDisplay(sf::Vector2f(630, 460));
    itemsDisplay.setFillColor(sf::Color(148, 75, 34, 200));
    itemsDisplay.setPosition(20, 60);

    sf::RectangleShape stats(sf::Vector2f(320, 760));
    stats.setFillColor(sf::Color(148, 75, 34, 200));
    stats.setPosition(680, 60);

    sf::RectangleShape iconsBackground(sf::Vector2f(660, 120));
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
            "backButton", "equipButton", "unequipButton", "buyButton", "armButton", "calfButton", "chestButton", "feetButton",
            "forearmButton", "helmetButton", "pantsButton", "shoulderButton", "thighButton"
        };
    }
    else {
        buttonsToDisplay = {"backButton", "equipButton", "buyButton", "swordButton", "unequipButton"};
    }

    for (const auto& buttonName : buttonsToDisplay) {
        if (buttons.find(buttonName) != buttons.end()) {
            const Button& button = buttons.at(buttonName);
            window.draw(button.getSprite());
        }
    }
}

void Shop::displayItems(sf::RenderWindow& window) {
    std::string itemName = shopModeToString();
    std::string itemNameRight = "";

    if (itemName.find("Left") != std::string::npos) {
        itemNameRight = itemName;
        itemNameRight.replace(itemNameRight.size() - 4, 4, "Right");
    }

    if (isArmorer) {
        auto range = availableArmorPieces.equal_range(itemName);

        for (auto it = range.first; it != range.second; ++it) {
            const ArmorPiece& armorPiece = it->second;
            window.draw(armorPiece.getSprite());
        }

        auto rangeRight = availableArmorPieces.equal_range(itemNameRight);

        for (auto it = rangeRight.first; it != rangeRight.second; ++it) {
            const ArmorPiece& armorPiece = it->second;
            window.draw(armorPiece.getSprite());
        }
    }
    else {
        auto range = availableWeapons.equal_range(itemName);
    
        for (auto it = range.first; it != range.second; ++it) {
            const Weapon& weapon = it->second;
            window.draw(weapon.getSprite());
        }

        auto rangeRight = availableWeapons.equal_range(itemNameRight);

        for (auto it = rangeRight.first; it != rangeRight.second; ++it) {
            const Weapon& weapon = it->second;
            window.draw(weapon.getSprite());
        }
    }
}

void Shop::setUpItemsPosition() {
    std::string itemName = shopModeToString();
    std::string itemNameRight = "";

    if (itemName.find("Left") != std::string::npos) {
        itemNameRight = itemName;
        itemNameRight.replace(itemNameRight.size() - 4, 4, "Right");
    }

    std::unordered_map<std::string, sf::Vector2f> positions;
    if (isArmorer) {
        for (auto& entry : availableArmorPieces) {
            const std::string& key = entry.first;
            ArmorPiece& armorPiece = entry.second;

            if (key == itemName || key == itemNameRight) {
                if (positions.find(itemName) == positions.end()) {
                    positions[itemName] = sf::Vector2f(50.0f, 80.0f);
                }

                armorPiece.setPosition(positions[itemName]);

                positions[itemName].x += 90.0f;

                if (positions[itemName].x > 580.0f) {
                    positions[itemName].x = 50.0f;
                    positions[itemName].y += 90.0f;
                }
            }
            else {
                if (positions.find(key) == positions.end()) {
                    armorPiece.setPosition(sf::Vector2f(-100.0f, -100.0f));
                }
            }
        }
    }
    else {
        for (auto& entry : availableWeapons) {
            const std::string& key = entry.first;
            Weapon& weapon = entry.second;

            if (key == itemName || key == itemNameRight) {
                if (positions.find(itemName) == positions.end()) {
                    positions[itemName] = sf::Vector2f(50.0f, 80.0f);
                }

                weapon.setPosition(positions[itemName]);

                positions[itemName].x += 90.0f;

                if (positions[itemName].x > 580.0f) {
                    positions[itemName].x = 50.0f;
                    positions[itemName].y += 90.0f;
                }
            }
            else {
                if (positions.find(key) == positions.end()) {
                    weapon.setPosition(sf::Vector2f(-100.0f, -100.0f));
                }
            }
        }
    }
}

void Shop::checkForClickedItems(const sf::Vector2f& mousePosition, Player& player) {
    if (isArmorer) {
        for (auto& pair : availableArmorPieces) {
            ArmorPiece& armorPiece = pair.second;
            if (armorPiece.isClicked(mousePosition)) {
                selectedArmorPiece = &armorPiece;
                displayBuyOrEquipButton(player);
                break;
            }
        }
    }
    else {
        for (auto& pair : availableWeapons) {
            Weapon& weapon = pair.second;
            if (weapon.isClicked(mousePosition)) {
                selectedWeapon = &weapon;
                displayBuyOrEquipButton(player);
                break;
            }
        }
    }
}

void Shop::displayBuyOrEquipButton(Player& player) {
    if (isArmorer) {
        auto it = boughtArmorPieces.find(selectedArmorPiece->getName() + selectedArmorPiece->getType());

        if (it != boughtArmorPieces.end()) {
            std::unordered_map<std::string, Button>& buttons = getButtons();

            bool itemBought = it->second;
            bool itemEquiped = player.isArmorPieceInMap(selectedArmorPiece);

            if (itemBought && itemEquiped) {
                if (buttons.find("equipButton") != buttons.end()) {
                    buttons.at("unequipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
                    buttons.at("equipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                    buttons.at("buyButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                }
            }
            else if (itemBought && !itemEquiped) {
                if (buttons.find("buyButton") != buttons.end()) {
                    buttons.at("equipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
                    buttons.at("unequipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                    buttons.at("buyButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                }
            }
            else {
                if (buttons.find("buyButton") != buttons.end()) {
                    buttons.at("buyButton").setPosition(sf::Vector2f(770.0f, 450.0f));
                    buttons.at("unequipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                    buttons.at("equipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                }
            }
        }
    }
    else {
        auto it = boughtWeapons.find(selectedWeapon->getName() + selectedWeapon->getType());

        if (it != boughtWeapons.end()) {
            std::unordered_map<std::string, Button>& buttons = getButtons();

            bool itemBought = it->second;
            bool itemEquiped = player.isWeaponInMap(selectedWeapon);

            if (itemBought && itemEquiped) {
                if (buttons.find("equipButton") != buttons.end()) {
                    buttons.at("unequipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
                    buttons.at("equipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                    buttons.at("buyButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                }
            }
            else if (itemBought && !itemEquiped) {
                if (buttons.find("buyButton") != buttons.end()) {
                    buttons.at("equipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
                    buttons.at("unequipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                    buttons.at("buyButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                }
            }
            else {
                if (buttons.find("buyButton") != buttons.end()) {
                    buttons.at("buyButton").setPosition(sf::Vector2f(770.0f, 450.0f));
                    buttons.at("unequipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                    buttons.at("equipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                }
            }
        }
    }
}

void Shop::changeButtonPosition(const std::string &buttonName, const sf::Vector2f& position) {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find(buttonName) != buttons.end()) {
        buttons.at(buttonName).setPosition(position);
    }
}

void Shop::displayStatsOfSelectedItem(sf::RenderWindow& window) {
    if (isArmorer) {
        if (selectedArmorPiece && currentMode != ShopMode::Nothing) {
            sf::Font font;
            if (!font.loadFromFile("Fonts/PlayfairDisplay.ttf")) {
            }

            sf::Text stats;
            float padding_x;
            stats.setFont(font);
            stats.setString("Stats");
            stats.setCharacterSize(40);
            stats.setFillColor(sf::Color::White);
            stats.setPosition(770.0f, 80.0f);
            window.draw(stats);

            stats.setCharacterSize(32);

            stats.setString(selectedArmorPiece->getName());
            stats.setPosition(700, 160.0f);
            window.draw(stats);

            stats.setString(selectedArmorPiece->getType());
            stats.setPosition(700, 200.0f);
            window.draw(stats);

            stats.setString("Defence :");
            stats.setPosition(700.0f, 280.0f);
            padding_x = stats.getPosition().x + stats.getLocalBounds().width + 40;
            window.draw(stats);

            stats.setString(std::to_string(selectedArmorPiece->getDefence()));
            stats.setPosition(padding_x, 280.0f);
            window.draw(stats);

            stats.setString("Price :");
            stats.setPosition(700.0f, 320.0f);
            padding_x = stats.getPosition().x + stats.getLocalBounds().width + 40;
            window.draw(stats);

            stats.setString(std::to_string(selectedArmorPiece->getPrice()));
            stats.setPosition(padding_x, 320.0f);
            window.draw(stats);
        }
    }
    else {
        if (selectedWeapon && currentMode != ShopMode::Nothing) {
            sf::Font font;
            if (!font.loadFromFile("Fonts/PlayfairDisplay.ttf")) {
            }

            sf::Text stats;
            float padding_x;
            stats.setFont(font);
            stats.setString("Stats");
            stats.setCharacterSize(40);
            stats.setFillColor(sf::Color::White);
            stats.setPosition(770.0f, 80.0f);
            window.draw(stats);

            stats.setCharacterSize(32);

            stats.setString(selectedWeapon->getName());
            stats.setPosition(700, 160.0f);
            window.draw(stats);

            stats.setString(selectedWeapon->getType());
            stats.setPosition(700, 200.0f);
            window.draw(stats);

            stats.setString("Attack :");
            stats.setPosition(700.0f, 280.0f);
            padding_x = stats.getPosition().x + stats.getLocalBounds().width + 40;
            window.draw(stats);

            stats.setString(std::to_string(selectedWeapon->getAttack()));
            stats.setPosition(padding_x, 280.0f);
            window.draw(stats);

            stats.setString("Price :");
            stats.setPosition(700.0f, 320.0f);
            padding_x = stats.getPosition().x + stats.getLocalBounds().width + 40;
            window.draw(stats);

            stats.setString(std::to_string(selectedWeapon->getPrice()));
            stats.setPosition(padding_x, 320.0f);
            window.draw(stats);
        }
    }
}

void Shop::setMode(ShopMode mode) {
    currentMode = mode;
}

Shop::ShopMode Shop::getMode() const {
    return currentMode;
}

std::string Shop::shopModeToString() const
{
    static const std::unordered_map<ShopMode, std::string> modeToStringMap = {
        {ShopMode::Nothing, "nothing"},
        {ShopMode::Head, "head"},
        {ShopMode::Chest, "chest"},
        {ShopMode::Shoulder, "shoulderLeft"},
        {ShopMode::Elbow, "elbowLeft"},
        {ShopMode::Arm, "armLeft"},
        {ShopMode::Pelvis, "pelvis"},
        {ShopMode::Thigh, "thighLeft"},
        {ShopMode::Leg, "legLeft"},
        {ShopMode::Foot, "footLeft"},
        {ShopMode::Sword, "handLeft"}
    };

    auto it = modeToStringMap.find(getMode());

    return (it != modeToStringMap.end()) ? it->second : "";
}

void Shop::setSelectedArmorPiece(ArmorPiece* selectedArmorPiece) {
    this->selectedArmorPiece = selectedArmorPiece;
}

void Shop::setSelectedWeapon(Weapon* selectedWeapon) {
    this->selectedWeapon = selectedWeapon;
}

void Shop::buyItem() {
    if (isArmorer) {
        auto it = boughtArmorPieces.find(selectedArmorPiece->getName() + selectedArmorPiece->getType());
        if (it != boughtArmorPieces.end()) {
            std::unordered_map<std::string, Button>& buttons = getButtons();

            bool itemIsBought = it->second;
            if (!itemIsBought) {
                if (buttons.find("unequipButton") != buttons.end() && buttons.find("buyButton") != buttons.end()) {
                    if (selectedArmorPiece->getPrice() <= player->getGold()) {
                        player->buy(selectedArmorPiece->getPrice());

                        it->second = true;
                        buttons.at("unequipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
                        buttons.at("buyButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                        buttons.at("equipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));

                        std::string characterPart = this->findKeyForArmorPiece(selectedArmorPiece);
                        player->addArmorPiece(characterPart, *selectedArmorPiece);
                        player->updateArmorAndWeaponPositions();
                    }
                }
            }
        }
    }
    else {
        auto it = boughtWeapons.find(selectedWeapon->getName() + selectedWeapon->getType());
        if (it != boughtWeapons.end()) {
            std::unordered_map<std::string, Button>& buttons = getButtons();

            bool itemIsBought = it->second;
            if (!itemIsBought) {
                if (buttons.find("equipButton") != buttons.end() && buttons.find("buyButton") != buttons.end()) {
                    if (selectedWeapon->getPrice() <= player->getGold()) {
                        player->buy(selectedWeapon->getPrice());

                        it->second = true;
                        buttons.at("unequipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
                        buttons.at("buyButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
                        buttons.at("equipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));

                        std::string characterPart = this->findKeyForWeapon(selectedWeapon);
                        player->addWeapon(characterPart, *selectedWeapon);
                        player->updateArmorAndWeaponPositions();
                    }
                }
            }
        }
    }
}

void Shop::equipItem() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (isArmorer) {
        if (player->isArmorPieceInMap(selectedArmorPiece)) {
            std::string characterPart = this->findKeyForArmorPiece(selectedArmorPiece);
            player->removeArmorPiece(characterPart);

            buttons.at("unequipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
            buttons.at("equipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
        }
        else {
            std::string characterPart = this->findKeyForArmorPiece(selectedArmorPiece);
            player->addArmorPiece(characterPart, *selectedArmorPiece);
            player->updateArmorAndWeaponPositions();

            buttons.at("unequipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
            buttons.at("equipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
        }
    }
    else {
        if (player->isWeaponInMap(selectedWeapon)) {
            std::string characterPart = this->findKeyForWeapon(selectedWeapon);
            player->removeWeapon(characterPart);

            buttons.at("unequipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
            buttons.at("equipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
        }
        else {
            std::string characterPart = this->findKeyForWeapon(selectedWeapon);
            player->addWeapon(characterPart, *selectedWeapon);
            player->updateArmorAndWeaponPositions();

            buttons.at("unequipButton").setPosition(sf::Vector2f(770.0f, 450.0f));
            buttons.at("equipButton").setPosition(sf::Vector2f(-100.0f, -100.0f));
        }
    }
}

std::string Shop::findKeyForArmorPiece(const ArmorPiece* selectedArmorPiece) const {
    auto it = std::find_if(availableArmorPieces.begin(), availableArmorPieces.end(),
        [selectedArmorPiece, this](const auto& pair) {
            return &pair.second == selectedArmorPiece;
        });

    if (it != availableArmorPieces.end()) {
        return it->first;
    }
    else {
        return "";
    }
}

std::string Shop::findKeyForWeapon(const Weapon* selectedWeapon) const {
    auto it = std::find_if(availableWeapons.begin(), availableWeapons.end(),
        [selectedWeapon, this](const auto& pair) {
            return &pair.second == selectedWeapon;
        });

    if (it != availableWeapons.end()) {
        return it->first;
    }
    else {
        return "";
    }
}