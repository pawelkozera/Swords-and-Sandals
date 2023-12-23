#pragma once

#include "PlaceInterface.h"
#include "Player.h"

class Arena : public PlaceInterface
{
private:
	void handleButtonClick(const std::string& buttonName, Player& player, Character &enemy);
	bool playerTurn;
public:
	Arena();
	Arena(sf::Texture& arenaTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons(Player& player);
	void checkForClickedButton(const sf::Vector2f& mousePosition, Player& player, Character &enemy);
	void handleEnemyMove(Character &enemy, Player &player);
	const bool getPlayerTurn();
};

