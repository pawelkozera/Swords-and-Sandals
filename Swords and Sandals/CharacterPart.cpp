#include "CharacterPart.h"

CharacterPart::CharacterPart(const sf::Texture& texture) {
    scaleX = 0.12f;
    scaleY = 0.12f;

    sprite.setTexture(texture);
    sprite.setPosition(200, 200);
    sprite.setScale(scaleX, scaleY);
}

sf::Sprite const CharacterPart::getSprite() const {
    return sprite;
}

sf::Vector2f const CharacterPart::getPosition() const {
    return position;
}

sf::FloatRect const CharacterPart::getSpriteSize() const {
    return sprite.getGlobalBounds();
}

void CharacterPart::setPosition(const sf::Vector2f position) {
    this->position = position;
}

void CharacterPart::flipSprite() {
    sprite.setScale(-scaleX, scaleY);
}
