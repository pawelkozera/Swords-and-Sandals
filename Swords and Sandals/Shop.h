#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ArmorPiece.h"
#include <unordered_map>

class Shop
{
private:
	std::unordered_map<std::string, ArmorPiece> availableArmorPieces;
	std::unordered_map<std::string, ArmorPiece> soldArmorPieces;
public:
	Shop(const sf::Texture& backgroundTexture, const std::vector<Button>& buttons);
};

