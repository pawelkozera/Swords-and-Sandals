#include "Shop.h"


Shop::Shop(std::unordered_map<std::string, Button> buttons, TextureManager& textureManager)
    : PlaceInterface(textureManager.getTexture("armorerBackground"), buttons) {
    isArmorer = true;
    this->armorer = &textureManager.getTexture("armorerBackground");
    this->weaponsmith = &textureManager.getTexture("weaponsmithBackground");
    setMode(ShopMode::Nothing);
    selectedArmorPiece = nullptr;

    availableArmorPieces.insert({ "head", ArmorPiece(textureManager.getTexture("DKAhead"), 1, 200, "Dark knight", "helmet")});
    availableArmorPieces.insert({ "chest", ArmorPiece(textureManager.getTexture("DKAchest"), 1, 500, "Dark knight", "breastplate")});
    availableArmorPieces.insert({ "shoulder", ArmorPiece(textureManager.getTexture("DKAshoulder"), 1, 300, "Dark knight", "shoulderguards")});
    availableArmorPieces.insert({ "elbow", ArmorPiece(textureManager.getTexture("DKAelbow"), 1, 300, "Dark knight", "gauntlets")});
    availableArmorPieces.insert({ "arm", ArmorPiece(textureManager.getTexture("DKAarm"), 1, 300, "Dark knight", "gloves")});
    availableArmorPieces.insert({ "pelvis", ArmorPiece(textureManager.getTexture("DKApelvis"), 1, 300, "Dark knight", "pants")});
    availableArmorPieces.insert({ "thigh", ArmorPiece(textureManager.getTexture("DKAthigh"), 1, 300, "Dark knight", "greaves")});
    availableArmorPieces.insert({ "leg", ArmorPiece(textureManager.getTexture("DKAleg"), 1, 300, "Dark knight", "shinguards")});
    availableArmorPieces.insert({ "foot", ArmorPiece(textureManager.getTexture("DKAfoot"), 1, 300, "Dark knight", "boots")});
    
    setUpItemsPosition();
}

Shop::Shop(){}

void Shop::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();

    if (buttons.find("backButton") != buttons.end()) {
        buttons.at("backButton").setPosition(sf::Vector2f(100.0f, 800.0f));
    }

    setUpPositionOfIconButtons();
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

void Shop::displayItems(sf::RenderWindow& window) {
    std::string itemName = shopModeToString();

    auto range = availableArmorPieces.equal_range(itemName);

    for (auto& it = range.first; it != range.second; ++it) {
        const ArmorPiece& armorPiece = it->second;
        window.draw(armorPiece.getSprite());
    }
}

void Shop::setUpItemsPosition() {
    std::string itemName = shopModeToString();

    std::unordered_map<std::string, sf::Vector2f> positions;

    for (auto& entry : availableArmorPieces) {
        const std::string& key = entry.first;
        ArmorPiece& armorPiece = entry.second;

        if (key == itemName) {
            if (positions.find(key) == positions.end()) {
                positions[key] = sf::Vector2f(50.0f, 80.0f);
            }

            armorPiece.setPosition(positions[key]);

            positions[key].x += 90.0f;

            if (positions[key].x > 580.0f) {
                positions[key].x = 50.0f;
                positions[key].y += 90.0f;
            }
        }
        else {
            if (positions.find(key) == positions.end()) {
                armorPiece.setPosition(sf::Vector2f(-100.0f, -100.0f));
            }
        }
    }
}

void Shop::checkForClickedItems(const sf::Vector2f& mousePosition) {
    if (isArmorer) {
        for (auto& pair : availableArmorPieces) {
            ArmorPiece& armorPiece = pair.second;
            if (armorPiece.isClicked(mousePosition)) {
                selectedArmorPiece = &armorPiece;
                break;
            }
        }
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
        {ShopMode::Shoulder, "shoulder"},
        {ShopMode::Elbow, "elbow"},
        {ShopMode::Arm, "arm"},
        {ShopMode::Pelvis, "pelvis"},
        {ShopMode::Thigh, "thigh"},
        {ShopMode::Leg, "leg"},
        {ShopMode::Foot, "foot"},
        {ShopMode::Sword, "sword"}
    };

    auto it = modeToStringMap.find(getMode());

    return (it != modeToStringMap.end()) ? it->second : "";
}

void Shop::setSelectedArmorPiece(ArmorPiece* selectedArmorPiece) {
    this->selectedArmorPiece = selectedArmorPiece;
}
