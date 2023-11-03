#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Cursor : public Object
{
private:
public:
	Cursor(const sf::Texture& texture);
};

