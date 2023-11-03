#include "Cursor.h"

Cursor::Cursor()
{
}

Cursor::Cursor(sf::Texture& texture, sf::RenderWindow& window) : Object(texture) {
    this->window = &window;
	setScale(1.0f, 1.0f);
    setCursorVisible(false);
}

void Cursor::update() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    setPosition(static_cast<sf::Vector2f>(mousePosition));
}

void Cursor::render() {
    window->draw(getSprite());
}

void Cursor::setCursorVisible(bool visible) {
    window->setMouseCursorVisible(visible);
}