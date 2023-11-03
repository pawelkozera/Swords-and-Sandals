#include "GameManager.h"

GameManager::GameManager(TextureManager &textureManager) : textureManager(textureManager) {
    window.create(sf::VideoMode(1024, 900), "Swords and Sandals");
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

        window.display();
    }
}

void GameManager::setUp() {
    std::unordered_map<std::string, CharacterPart> characterPartsMap = createCharacterPartsMap();
    std::unordered_map<std::string, ArmorPiece> characterArmorPieces = createCharacterArmorPieces();
    std::unordered_map<std::string, Button> Buttons = createCityCenterButtonsMap();

    character = Character(characterPartsMap, characterArmorPieces);
    cityCenter = CityCenter(textureManager.getTexture("cityCenter"), Buttons);

    cityCenter.setUpPositionOfButtons();
    character.assembleBody();
    character.updateArmorPositions();

    gameState = GameState();
}

void GameManager::handleEvents() {
    switch (gameState.getMode()) {
    case GameState::GameMode::InCity:
        cityCenter.displayCity(window);
        cityCenter.displayButtons(window);
        break;
    case GameState::GameMode::InWeaponsmithShop:
        break;
    case GameState::GameMode::InArmorerShop:
        break;
    case GameState::GameMode::InArena:
        break;
    default:
        break;
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