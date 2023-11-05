#include "GameManager.h"

GameManager::GameManager(TextureManager &textureManager) : textureManager(textureManager) {
    window.create(sf::VideoMode(1024, 900), "Swords and Sandals");

    buttonHandlers["backButton"] = [this]() {
        gameState.setMode(GameState::GameMode::InCity);
        };
    buttonHandlers["helmetButton"] = [this]() {
        };
    buttonHandlers["shoulderButton"] = [this]() {
        };
    buttonHandlers["forearmButton"] = [this]() {
        };
    buttonHandlers["armButton"] = [this]() {
        };
    buttonHandlers["pantsButton"] = [this]() {
        };
    buttonHandlers["thighButton"] = [this]() {
        };
    buttonHandlers["calfButton"] = [this]() {
        };
    buttonHandlers["feetButton"] = [this]() {
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
        //character.display(window);

        cursor.update();
        cursor.render();

        window.display();
    }
}

void GameManager::setUp() {
    std::unordered_map<std::string, CharacterPart> characterPartsMap = createCharacterPartsMap();
    std::unordered_map<std::string, ArmorPiece> characterArmorPieces = createCharacterArmorPieces();
    std::unordered_map<std::string, Button> cityCenterButtons = createCityCenterButtonsMap();
    std::unordered_map<std::string, Button> shopButtons = createShopButtonsMap();

    character = Character(characterPartsMap, characterArmorPieces);
    cityCenter = CityCenter(textureManager.getTexture("cityCenter"), cityCenterButtons);
    shop = Shop(textureManager.getTexture("armorerBackground"), textureManager.getTexture("weaponsmithBackground"), shopButtons);

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
        shop.setShopToArmorer(false);
        shop.displayBackground(window);
        shop.displayButtons(window);
        handleShopArmorerButtons();
        break;
    case GameState::GameMode::InArmorerShop:
        shop.setShopToArmorer(true);
        shop.displayBackground(window);
        shop.displayInterface(window);
        shop.displayButtons(window);
        handleShopArmorerButtons();
        break;
    case GameState::GameMode::InArena:
        break;
    default:
        break;
    }
}

void GameManager::handleCityCenterButtons() {
    if (cityCenter.getButton("arena").isClicked(cursor.getPosition())) {
        gameState.setMode(GameState::GameMode::InArena);
    }
    else if (cityCenter.getButton("armorer").isClicked(cursor.getPosition())) {
        gameState.setMode(GameState::GameMode::InArmorerShop);
    }
    else if (cityCenter.getButton("weaponsmith").isClicked(cursor.getPosition())) {
        gameState.setMode(GameState::GameMode::InWeaponsmithShop);
    }
}

void GameManager::handleShopArmorerButtons() {
    for (const auto& pair : shop.getButtons()) {
        const std::string& buttonName = pair.first;
        const Button& button = pair.second;

        if (button.isClicked(cursor.getPosition())) {
            if (buttonHandlers.find(buttonName) != buttonHandlers.end()) {
                buttonHandlers[buttonName]();
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

std::unordered_map<std::string, ArmorPiece> GameManager::createCharacterArmorPieces() {
    std::unordered_map<std::string, ArmorPiece> characterArmorPiecesMap;

    ArmorPiece armorPieceHead(textureManager.getTexture("DKAhead"));
    ArmorPiece armorPieceChest(textureManager.getTexture("DKAchest"));
    ArmorPiece armorPieceShoulder(textureManager.getTexture("DKAshoulder"));
    ArmorPiece armorPieceElbow(textureManager.getTexture("DKAelbow"));
    ArmorPiece armorPieceArm(textureManager.getTexture("DKAarm"));
    ArmorPiece armorPiecePelvis(textureManager.getTexture("DKApelvis"));
    ArmorPiece armorPieceThigh(textureManager.getTexture("DKAthigh"));
    ArmorPiece armorPieceLeg(textureManager.getTexture("DKAleg"));
    ArmorPiece armorPieceFoot(textureManager.getTexture("DKAfoot"));

    characterArmorPiecesMap.insert_or_assign("head", armorPieceHead);
    characterArmorPiecesMap.insert_or_assign("chest", armorPieceChest);
    characterArmorPiecesMap.insert_or_assign("shoulderLeft", armorPieceShoulder);
    armorPieceShoulder.flipSprite();
    characterArmorPiecesMap.insert_or_assign("shoulderRight", armorPieceShoulder);
    characterArmorPiecesMap.insert_or_assign("elbowLeft", armorPieceElbow);
    armorPieceElbow.flipSprite();
    characterArmorPiecesMap.insert_or_assign("elbowRight", armorPieceElbow);
    characterArmorPiecesMap.insert_or_assign("armLeft", armorPieceArm);
    armorPieceArm.flipSprite();
    characterArmorPiecesMap.insert_or_assign("armRight", armorPieceArm);
    characterArmorPiecesMap.insert_or_assign("pelvis", armorPiecePelvis);
    characterArmorPiecesMap.insert_or_assign("thighLeft", armorPieceThigh);
    armorPieceThigh.flipSprite();
    characterArmorPiecesMap.insert_or_assign("thighRight", armorPieceThigh);
    characterArmorPiecesMap.insert_or_assign("legLeft", armorPieceLeg);
    armorPieceLeg.flipSprite();
    characterArmorPiecesMap.insert_or_assign("legRight", armorPieceLeg);
    characterArmorPiecesMap.insert_or_assign("footLeft", armorPieceFoot);
    armorPieceFoot.flipSprite();
    characterArmorPiecesMap.insert_or_assign("footRight", armorPieceFoot);

    return characterArmorPiecesMap;
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
    Button swordButton(textureManager.getTexture("swordIcon"));
    Button thighButton(textureManager.getTexture("thighIcon"));

    Buttons.insert_or_assign("armButton", armButton);
    Buttons.insert_or_assign("calfButton", calfButton);
    Buttons.insert_or_assign("chestButton", chestButton);
    Buttons.insert_or_assign("feetButton", feetButton);
    Buttons.insert_or_assign("forearmButton", forearmButton);
    Buttons.insert_or_assign("helmetButton", helmetButton);
    Buttons.insert_or_assign("pantsButton", pantsButton);
    Buttons.insert_or_assign("shoulderButton", shoulderButton);
    Buttons.insert_or_assign("swordButton", swordButton);
    Buttons.insert_or_assign("thighButton", thighButton);

    for (auto& pair : Buttons) {
        Button& button = pair.second;
        button.setScale(0.15f, 0.15f);
    }

    Buttons.insert_or_assign("backButton", backButton);

    return Buttons;
}