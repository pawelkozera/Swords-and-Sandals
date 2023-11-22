#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ArmorPiece.h"
#include <unordered_map>
#include "PlaceInterface.h"
#include "TextureManager.h"
#include "Player.h"

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
		Foot,
		Sword
	};

	Shop();
	Shop(std::unordered_map<std::string, Button> buttons, TextureManager &textureManager, Player* player);
	void setUpPositionOfButtons() override;
	void setUpPositionOfIconButtons();
	void setShopToArmorer(bool isArmorer);
	void displayInterface(sf::RenderWindow& window);
	void displayButtons(sf::RenderWindow& window);
	void displayItems(sf::RenderWindow& window);
	void setUpItemsPosition();
	void checkForClickedItems(const sf::Vector2f& mousePosition);
	void displayBuyOrEquipButton();
	void changeButtonPosition(const std::string& buttonName, const sf::Vector2f& position);
	void displayStatsOfSelectedItem(sf::RenderWindow& window);
	void setMode(ShopMode mode);
	ShopMode getMode() const;
	std::string shopModeToString() const;
	void setSelectedArmorPiece(ArmorPiece* selectedArmorPiece);
	void buyItem();
private:
	ShopMode currentMode;
	sf::Texture* armorer;
	sf::Texture* weaponsmith;
	Player* player;
	bool isArmorer;
	std::unordered_multimap<std::string, ArmorPiece> availableArmorPieces;
	std::unordered_map<std::string, bool> boughtArmorPieces;

	ArmorPiece* selectedArmorPiece;

	std::string findKeyForArmorPiece(const ArmorPiece* selectedArmorPiece) const;
};

