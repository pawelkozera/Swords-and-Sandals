#include "GameManager.h"

GameManager::GameManager() {
    window.create(sf::VideoMode(1000, 800), "Swords and Sandals");
}

void GameManager::run(TextureManager &textureManager) {
    std::unordered_map<std::string, CharacterPart> characterPartsMap = createCharacterPartsMap(textureManager);
    Character character(characterPartsMap);
    character.assembleBody();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color(50, 100, 200));
        character.display(window);
        window.display();
    }
}

std::unordered_map<std::string, CharacterPart> GameManager::createCharacterPartsMap(TextureManager& textureManager) {
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
