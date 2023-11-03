#include "Character.h"

Character::Character()
{
}

Character::Character(std::unordered_map<std::string, CharacterPart> &characterParts, std::unordered_map<std::string, ArmorPiece> &armorPieces)
	: characterParts(characterParts), armorPieces(armorPieces) {
}

void Character::assembleBody() {
    sf::Vector2f bodyPosition(300.0f, 200.0f);
    
    sf::Vector2f chestPosition = bodyPosition;

    sf::Vector2f headOffset(characterParts.at("chest").getSpriteRect().width / 8, -characterParts.at("head").getSpriteRect().height + 10.0f);
    sf::Vector2f shoulderLeftOffset(characterParts.at("shoulderLeft").getSpriteRect().width - 6.0f, characterParts.at("chest").getSpriteRect().height / -10);
    sf::Vector2f shoulderRightOffset(characterParts.at("chest").getSpriteRect().width + characterParts.at("shoulderRight").getSpriteRect().width - 6.0f, characterParts.at("chest").getSpriteRect().height / 10);
    sf::Vector2f elbowLeftOffset(0.0f, characterParts.at("shoulderLeft").getSpriteRect().height - 5.0f);
    sf::Vector2f elbowRightOffset(0.0f, characterParts.at("shoulderRight").getSpriteRect().height - 5.0f);
    sf::Vector2f armLeftOffset(0.0f, characterParts.at("elbowLeft").getSpriteRect().height - 5.0f);
    sf::Vector2f armRightOffset(0.0f, characterParts.at("elbowRight").getSpriteRect().height - 5.0f);
    sf::Vector2f pelvisOffset(characterParts.at("chest").getSpriteRect().width / 4, characterParts.at("chest").getSpriteRect().height - 5.0f);
    sf::Vector2f thighLeftOffset(characterParts.at("pelvis").getSpriteRect().width / -2, characterParts.at("pelvis").getSpriteRect().height / 3);
    sf::Vector2f thighRightOffset(characterParts.at("pelvis").getSpriteRect().width * 1.5, characterParts.at("pelvis").getSpriteRect().height / 3);
    sf::Vector2f legLeftOffset(0.0f, characterParts.at("thighLeft").getSpriteRect().height - 6.0f);
    sf::Vector2f legRightOffset(0.0f, characterParts.at("thighRight").getSpriteRect().height - 6.0f);
    sf::Vector2f footLeftOffset(characterParts.at("footLeft").getSpriteRect().width / -1.7f, characterParts.at("legLeft").getSpriteRect().height - 10.0f);
    sf::Vector2f footRightOffset(characterParts.at("footRight").getSpriteRect().width / 1.7f, characterParts.at("legRight").getSpriteRect().height - 10.0f);

    sf::Vector2f headPosition = chestPosition + headOffset;
    sf::Vector2f shoulderLeftPosition = chestPosition - shoulderLeftOffset;
    sf::Vector2f shoulderRightPosition = chestPosition + shoulderRightOffset;
    sf::Vector2f elbowLeftPosition = shoulderLeftPosition + elbowLeftOffset;
    sf::Vector2f elbowRightPosition = shoulderRightPosition + elbowRightOffset;
    sf::Vector2f armLeftPosition = elbowLeftPosition + armLeftOffset;
    sf::Vector2f armRightPosition = elbowRightPosition + armRightOffset;
    sf::Vector2f pelvisPosition = chestPosition + pelvisOffset;
    sf::Vector2f thighLeftPosition = pelvisPosition + thighLeftOffset;
    sf::Vector2f thighRightPosition = pelvisPosition + thighRightOffset;
    sf::Vector2f legLeftPosition = thighLeftPosition + legLeftOffset;
    sf::Vector2f legRightPosition = thighRightPosition + legRightOffset;
    sf::Vector2f footLeftPosition = legLeftPosition + footLeftOffset;
    sf::Vector2f footRightPosition = legRightPosition + footRightOffset;

    characterParts.at("head").setPosition(headPosition);
    characterParts.at("chest").setPosition(chestPosition);
    characterParts.at("shoulderLeft").setPosition(shoulderLeftPosition);
    characterParts.at("shoulderRight").setPosition(shoulderRightPosition);
    characterParts.at("elbowLeft").setPosition(elbowLeftPosition);
    characterParts.at("elbowRight").setPosition(elbowRightPosition);
    characterParts.at("armLeft").setPosition(armLeftPosition);
    characterParts.at("armRight").setPosition(armRightPosition);
    characterParts.at("pelvis").setPosition(pelvisPosition);
    characterParts.at("thighLeft").setPosition(thighLeftPosition);
    characterParts.at("thighRight").setPosition(thighRightPosition);
    characterParts.at("legLeft").setPosition(legLeftPosition);
    characterParts.at("legRight").setPosition(legRightPosition);
    characterParts.at("footLeft").setPosition(footLeftPosition);
    characterParts.at("footRight").setPosition(footRightPosition);
}

void Character::updateArmorPositions() {
    for (const auto& characterPartPair : characterParts) {
        const std::string& partKey = characterPartPair.first;
        if (armorPieces.find(partKey) != armorPieces.end()) {
            armorPieces.at(partKey).setPosition(characterPartPair.second.getPosition());
        }
    }
}

void Character::display(sf::RenderWindow& window) {
    std::vector<std::string> const renderOrderBody = {
        "chest", "head", "shoulderLeft", "shoulderRight", "elbowLeft", "elbowRight", "armLeft", "armRight", 
        "thighLeft", "thighRight", "pelvis", "legLeft", "legRight", "footLeft", "footRight"
    };

    for (const std::string &partName : renderOrderBody) {
        if (characterParts.find(partName) != characterParts.end()) {
            const CharacterPart& part = characterParts.at(partName);
            sf::Sprite sprite = part.getSprite();
            sprite.setPosition(part.getPosition());
            window.draw(sprite);
        }
    }

    std::vector<std::string> const renderOrderArmor = {
        "pelvis", "chest", "head", "shoulderLeft", "shoulderRight", "elbowLeft", "elbowRight", "armLeft", "armRight",
        "thighLeft", "thighRight", "footLeft", "footRight", "legLeft", "legRight"
    };

    for (const std::string& partName : renderOrderArmor) {
        if (armorPieces.find(partName) != armorPieces.end()) {
            const ArmorPiece& part = armorPieces.at(partName);
            sf::Sprite sprite = part.getSprite();
            sprite.setPosition(part.getPosition());
            window.draw(sprite);
        }
    }
}

