#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ArmorPiece.h"
#include <unordered_map>
#include "PlaceInterface.h"
#include "TextureManager.h"

class Shop : public PlaceInterface
{
public:
	enum class ShopMode {
		Nothing,
		Head,
		Chest,
		Shoulder,
		Elbow,
		Arm,
		Pelvis,
		Thigh,
		Leg,
		Foot
	};

	Shop();
	Shop(std::unordered_map<std::string, Button> buttons, TextureManager &textureManager);
	void setUpPositionOfButtons() override;
	void setShopToArmorer(bool isArmorer);
	void displayInterface(sf::RenderWindow& window);
	void displayButtons(sf::RenderWindow& window);
	void displayItems(sf::RenderWindow& window);
	void checkForClickedItems(const sf::Vector2f& mousePosition);
	void displayStatsOfSelectedItem(sf::RenderWindow& window);
	void setMode(ShopMode mode);
	ShopMode getMode() const;
private:
	ShopMode currentMode;
	sf::Texture* armorer;
	sf::Texture* weaponsmith;
	bool isArmorer;
	std::unordered_multimap<std::string, ArmorPiece> availableArmorPieces;
	ArmorPiece* selectedArmorPiece;
	void setUpPositionOfButtonsArmorer(std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtonsWeaponsmith(std::unordered_map<std::string, Button>& buttons);
	void setUpItemsPosition();
};

