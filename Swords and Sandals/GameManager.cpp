#include "GameManager.h"

GameManager::GameManager(TextureManager &textureManager) : textureManager(textureManager) {
    window.create(sf::VideoMode(1024, 900), "Swords and Sandals");

    buttonHandlers["backButton"] = [this]() {
        gameState.setMode(GameState::GameMode::InCity);
        shop.setMode(Shop::ShopMode::Nothing);
        shop.setSelectedArmorPiece(nullptr);
        shop.changeButtonPosition("equipButton", sf::Vector2f(-100.0f, -100.0f));
        shop.changeButtonPosition("buyButton", sf::Vector2f(-100.0f, -100.0f));
        };
    buttonHandlers["helmetButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Head);
        };
    buttonHandlers["chestButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Chest);
        };
    buttonHandlers["shoulderButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Shoulder);
        };
    buttonHandlers["forearmButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Elbow);
        };
    buttonHandlers["armButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Arm);
        };
    buttonHandlers["pantsButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Pelvis);
        };
    buttonHandlers["thighButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Thigh);
        };
    buttonHandlers["calfButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Leg);
        };
    buttonHandlers["feetButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Foot);
        };
    buttonHandlers["swordButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Sword);
        };
}

void GameManager::run() {
    setUp();

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        handleEvents();

        cursor.update();
        cursor.render();

        window.display();
    }
}

void GameManager::setUp() {
    std::unordered_map<std::string, CharacterPart> characterPartsMap = createCharacterPartsMap();
    std::unordered_map<std::string, Button> cityCenterButtons = createCityCenterButtonsMap();
    std::unordered_map<std::string, Button> shopButtons = createShopButtonsMap();

    character = Character(characterPartsMap);
    cityCenter = CityCenter(textureManager.getTexture("cityCenter"), cityCenterButtons);
    shop = Shop(shopButtons, textureManager);

    cityCenter.setUpPositionOfButtons();
    shop.setUpPositionOfButtons();
    character.assembleBody();
    character.updateArmorPositions();

    gameState = GameState();

    cursor = Cursor(textureManager.getTexture("cursor"), window);
}

void GameManager::handleEvents() {
    switch (gameState.getMode()) {
    case GameState::GameMode::InCity:
        cityCenter.displayBackground(window);
        cityCenter.displayButtons(window);
        handleCityCenterButtons();
        break;
    case GameState::GameMode::InWeaponsmithShop:
        handleShopEvents();
        break;
    case GameState::GameMode::InArmorerShop:
        handleShopEvents();
        break;
    case GameState::GameMode::InArena:
        character.display(window);
        break;
    default:
        break;
    }
}

void GameManager::handleShopEvents() {
    shop.displayBackground(window);
    shop.displayInterface(window);
    shop.displayButtons(window);
    shop.displayItems(window);
    handleShopButtons();
    shop.checkForClickedItems(cursor.getPosition());
    shop.displayStatsOfSelectedItem(window);
}

void GameManager::handleCityCenterButtons() {
    if (cityCenter.getButton("arena").isClicked(cursor.getPosition())) {
        gameState.setMode(GameState::GameMode::InArena);
    }
    else if (cityCenter.getButton("armorer").isClicked(cursor.getPosition())) {
        gameState.setMode(GameState::GameMode::InArmorerShop);
        shop.setShopToArmorer(true);
        shop.setUpPositionOfIconButtons();
    }
    else if (cityCenter.getButton("weaponsmith").isClicked(cursor.getPosition())) {
        gameState.setMode(GameState::GameMode::InWeaponsmithShop);
        shop.setShopToArmorer(false);
        shop.setUpPositionOfIconButtons();
    }
}

void GameManager::handleShopButtons() {
    for (const auto& pair : shop.getButtons()) {
        const std::string& buttonName = pair.first;
        const Button& button = pair.second;

        if (button.isClicked(cursor.getPosition())) {
            if (buttonHandlers.find(buttonName) != buttonHandlers.end()) {
                buttonHandlers[buttonName]();
                shop.setUpItemsPosition();
                break;
            }
        }
    }
}

std::unordered_map<std::string, CharacterPart> GameManager::createCharacterPartsMap() {
    std::unordered_map<std::string, CharacterPart> characterPartsMap;

    CharacterPart characterPartHead(textureManager.getTexture("head"));
    CharacterPart characterPartChest(textureManager.getTexture("chest"));
    CharacterPart characterPartShoulder(textureManager.getTexture("shoulder"));
    CharacterPart characterPartElbow(textureManager.getTexture("elbow"));
    CharacterPart characterPartArm(textureManager.getTexture("arm"));
    CharacterPart characterPartPelvis(textureManager.getTexture("pelvis"));
    CharacterPart characterPartThigh(textureManager.getTexture("thigh"));
    CharacterPart characterPartLeg(textureManager.getTexture("leg"));
    CharacterPart characterPartFoot(textureManager.getTexture("foot"));

    characterPartsMap.insert_or_assign("head", characterPartHead);
    characterPartsMap.insert_or_assign("chest", characterPartChest);
    characterPartsMap.insert_or_assign("shoulderLeft", characterPartShoulder);
    characterPartShoulder.flipSprite();
    characterPartsMap.insert_or_assign("shoulderRight", characterPartShoulder);
    characterPartsMap.insert_or_assign("elbowLeft", characterPartElbow);
    characterPartElbow.flipSprite();
    characterPartsMap.insert_or_assign("elbowRight", characterPartElbow);
    characterPartsMap.insert_or_assign("armLeft", characterPartArm);
    characterPartArm.flipSprite();
    characterPartsMap.insert_or_assign("armRight", characterPartArm);
    characterPartsMap.insert_or_assign("pelvis", characterPartPelvis);
    characterPartsMap.insert_or_assign("thighLeft", characterPartThigh);
    characterPartThigh.flipSprite();
    characterPartsMap.insert_or_assign("thighRight", characterPartThigh);
    characterPartsMap.insert_or_assign("legLeft", characterPartLeg);
    characterPartLeg.flipSprite();
    characterPartsMap.insert_or_assign("legRight", characterPartLeg);
    characterPartsMap.insert_or_assign("footLeft", characterPartFoot);
    characterPartFoot.flipSprite();
    characterPartsMap.insert_or_assign("footRight", characterPartFoot);

    return characterPartsMap;
}

std::unordered_map<std::string, Button> GameManager::createCityCenterButtonsMap() {
    std::unordered_map<std::string, Button> Buttons;

    Button arenaButton(textureManager.getTexture("arenaButton"));
    Button armorerButton(textureManager.getTexture("armorerButton"));
    Button weaponsmithButton(textureManager.getTexture("weaponsmithButton"));

    Buttons.insert_or_assign("arena", arenaButton);
    Buttons.insert_or_assign("armorer", armorerButton);
    Buttons.insert_or_assign("weaponsmith", weaponsmithButton);

    return Buttons;
}

std::unordered_map<std::string, Button> GameManager::createShopButtonsMap() {
    std::unordered_map<std::string, Button> Buttons;

    Button backButton(textureManager.getTexture("backButton"));
    Button armButton(textureManager.getTexture("armIcon"));
    Button calfButton(textureManager.getTexture("calfIcon"));
    Button chestButton(textureManager.getTexture("chestIcon"));
    Button feetButton(textureManager.getTexture("feetIcon"));
    Button forearmButton(textureManager.getTexture("forearm_icon"));
    Button helmetButton(textureManager.getTexture("hemletIcon"));
    Button pantsButton(textureManager.getTexture("pantsIcon"));
    Button shoulderButton(textureManager.getTexture("shoulderIcon"));
    Button thighButton(textureManager.getTexture("thighIcon"));
    Button swordButton(textureManager.getTexture("swordIcon"));
    Button buyButton(textureManager.getTexture("buyButton"));
    Button equipButton(textureManager.getTexture("equipButton"));

    Buttons.insert_or_assign("armButton", armButton);
    Buttons.insert_or_assign("calfButton", calfButton);
    Buttons.insert_or_assign("chestButton", chestButton);
    Buttons.insert_or_assign("feetButton", feetButton);
    Buttons.insert_or_assign("forearmButton", forearmButton);
    Buttons.insert_or_assign("helmetButton", helmetButton);
    Buttons.insert_or_assign("pantsButton", pantsButton);
    Buttons.insert_or_assign("shoulderButton", shoulderButton);
    Buttons.insert_or_assign("thighButton", thighButton);
    Buttons.insert_or_assign("swordButton", swordButton);

    for (auto& pair : Buttons) {
        Button& button = pair.second;
        button.setScale(0.15f, 0.15f);
    }

    Buttons.insert_or_assign("backButton", backButton);
    Buttons.insert_or_assign("buyButton", buyButton);
    Buttons.insert_or_assign("equipButton", equipButton);

    return Buttons;
}