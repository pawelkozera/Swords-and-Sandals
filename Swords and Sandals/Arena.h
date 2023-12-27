#pragma once

#include "PlaceInterface.h"
#include "Player.h"
#include "GameState.h"

class Arena : public PlaceInterface
{
private:
	bool playerTurn;
	bool fightInProgress;
	bool playerWon;

	void handleButtonClick(const std::string& buttonName, Player& player, Character &enemy, GameState &gameState);
	void handleButtonClickFightInProgress(const std::string& buttonName, Player& player, Character& enemy);
	void handleButtonClickFightEnded(const std::string& buttonName, GameState& gameState);
	void setUpEndOfFightPositionOfButtons();
public:
	Arena();
	Arena(sf::Texture& arenaTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons(Player& player);
	void checkForClickedButton(const sf::Vector2f& mousePosition, Player& player, Character &enemy, GameState& gameState);
	void displayEndOfFight(sf::RenderWindow& window);
	void handleEnemyMove(Character &enemy, Player &player);
	const bool getPlayerTurn();
	const bool getFightInProgress();
	void setFightInProgress(bool fightState);
};

