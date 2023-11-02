#include "Object.h"

Object::Object(const sf::Texture& texture) {
    scaleX = 0.12f;
    scaleY = 0.12f;

    sprite.setTexture(texture);
    sprite.setPosition(200, 200);
    sprite.setScale(scaleX, scaleY);
}

sf::Sprite const &Object::getSprite() const {
    return sprite;
}

sf::Vector2f const Object::getPosition() const {
    return position;
}

sf::FloatRect const Object::getSpriteRect() const {
    return sprite.getGlobalBounds();
}

void Object::setPosition(const sf::Vector2f position) {
    this->position = position;
}

void Object::flipSprite() {
    sprite.setScale(-scaleX, scaleY);
}

void Object::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}