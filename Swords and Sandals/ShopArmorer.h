#pragma once

#include "Shop.h"

class ShopArmorer : public Shop
{
private:
	std::unordered_map<std::string, ArmorPiece> availableArmors;
	std::unordered_map<std::string, ArmorPiece> soldArmors;
public:
	ShopArmorer(const sf::Texture& backgroundTexture, const std::vector<Button>& buttons);
};

