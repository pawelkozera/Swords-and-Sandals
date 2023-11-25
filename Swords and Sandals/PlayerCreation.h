#pragma once

#include "PlaceInterface.h"
#include "Player.h"
#include "GameState.h"

class PlayerCreation : public PlaceInterface
{
private:
	void handleButtonClick(const std::string& buttonName, Player& player, GameState& gameState);
	void setOldStats(Player &player);
	void handlePlusButtonClick(const std::string& buttonName, Player& player);
	void handleMinusButtonClick(const std::string& buttonName, Player& player);

	int oldStrength;
	int oldAgility;
	int oldAttack;
	int oldDefence;
	int oldVitality;
	int oldCharisma;
	int oldStamina;
public:
	PlayerCreation();
	PlayerCreation(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons() override;
	void displayInterface(sf::RenderWindow&window, Player &player);
	void checkForClickedButton(const sf::Vector2f& mousePosition, Player &player, GameState &gameState);
};

