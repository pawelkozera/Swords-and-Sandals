#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Cursor : public Object
{
private:
	sf::RenderWindow* window;
public:
	Cursor();
	Cursor(sf::Texture& texture, sf::RenderWindow &window);
	void update();
	void render();
	void setCursorVisible(bool visible);
};

