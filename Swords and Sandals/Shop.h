#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ArmorPiece.h"
#include <unordered_map>
#include "PlaceInterface.h"

class Shop : public PlaceInterface
{
private:
	sf::Texture armorer;
	sf::Texture weaponsmith;
	bool isArmorer;
	std::unordered_map<std::string, ArmorPiece> availableArmorPieces;
	std::unordered_map<std::string, ArmorPiece> soldArmorPieces;
public:
	Shop();
	Shop(sf::Texture& armorer, sf::Texture& weaponsmith, std::unordered_map<std::string, Button> buttons);
	void setUpPositionOfButtons() override;
	void setShopToArmorer(bool isArmorer);
};

