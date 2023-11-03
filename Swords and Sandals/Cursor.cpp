#include "Cursor.h"

Cursor::Cursor(const sf::Texture& texture) : Object(texture) {
	setScale(1.0f, 1.0f);
}