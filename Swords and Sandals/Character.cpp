#include "Character.h"

Character::Character(std::unordered_map<std::string, CharacterPart> characterParts) 
	: characterParts(characterParts) {
}

void Character::assembleBody() {
    sf::Vector2f bodyPosition(300.0f, 200.0f);
    
    sf::Vector2f chestPosition = bodyPosition;

    sf::Vector2f headOffset(characterParts.at("chest").getSpriteSize().width / 8, -characterParts.at("head").getSpriteSize().height + 10.0f);
    sf::Vector2f shoulderLeftOffset(characterParts.at("shoulderLeft").getSpriteSize().width - 6.0f, characterParts.at("chest").getSpriteSize().height / -10);
    sf::Vector2f shoulderRightOffset(characterParts.at("chest").getSpriteSize().width + characterParts.at("shoulderRight").getSpriteSize().width - 6.0f, characterParts.at("chest").getSpriteSize().height / 10);
    sf::Vector2f elbowLeftOffset(0.0f, characterParts.at("shoulderLeft").getSpriteSize().height - 5.0f);
    sf::Vector2f elbowRightOffset(0.0f, characterParts.at("shoulderRight").getSpriteSize().height - 5.0f);
    sf::Vector2f armLeftOffset(0.0f, characterParts.at("elbowLeft").getSpriteSize().height - 5.0f);
    sf::Vector2f armRightOffset(0.0f, characterParts.at("elbowRight").getSpriteSize().height - 5.0f);
    sf::Vector2f pelvisOffset(characterParts.at("chest").getSpriteSize().width / 4, characterParts.at("chest").getSpriteSize().height - 5.0f);
    sf::Vector2f thighLeftOffset(characterParts.at("pelvis").getSpriteSize().width / -2, characterParts.at("pelvis").getSpriteSize().height / 3);
    sf::Vector2f thighRightOffset(characterParts.at("pelvis").getSpriteSize().width * 1.5, characterParts.at("pelvis").getSpriteSize().height / 3);
    sf::Vector2f legLeftOffset(0.0f, characterParts.at("thighLeft").getSpriteSize().height - 6.0f);
    sf::Vector2f legRightOffset(0.0f, characterParts.at("thighRight").getSpriteSize().height - 6.0f);
    sf::Vector2f footLeftOffset(characterParts.at("footLeft").getSpriteSize().width / -1.7f, characterParts.at("legLeft").getSpriteSize().height - 10.0f);
    sf::Vector2f footRightOffset(characterParts.at("footRight").getSpriteSize().width / 1.7f, characterParts.at("legRight").getSpriteSize().height - 10.0f);

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

void Character::display(sf::RenderWindow& window) {
    std::vector<std::string> const renderOrder = {
        "chest", "head", "shoulderLeft", "shoulderRight", "elbowLeft", "elbowRight", "armLeft", "armRight", 
        "thighLeft", "thighRight", "pelvis", "legLeft", "legRight", "footLeft", "footRight"
    };

    for (const std::string &partName : renderOrder) {
        if (characterParts.find(partName) != characterParts.end()) {
            const CharacterPart& part = characterParts.at(partName);
            sf::Sprite sprite = part.getSprite();
            sprite.setPosition(part.getPosition());
            window.draw(sprite);
        }
    }

}
