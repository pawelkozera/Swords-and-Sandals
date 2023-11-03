#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ArmorPiece.h"
#include <unordered_map>

class Shop
{
private:
public:
	Shop(const sf::Texture& backgroundTexture, const std::vector<Button>& buttons);
};

