#include "ArmorPiece.h"


ArmorPiece::ArmorPiece(const sf::Texture& texture) {
    scaleX = 0.12f;
    scaleY = 0.12f;

    sprite.setTexture(texture);
    sprite.setPosition(200, 200);
    sprite.setScale(scaleX, scaleY);
}

sf::Sprite const ArmorPiece::getSprite() const {
    return sprite;
}

sf::Vector2f const ArmorPiece::getPosition() const {
    return position;
}

sf::FloatRect const ArmorPiece::getSpriteSize() const {
    return sprite.getGlobalBounds();
}

void ArmorPiece::setPosition(const sf::Vector2f position) {
    this->position = position;
}

void ArmorPiece::flipSprite() {
    sprite.setScale(-scaleX, scaleY);
}