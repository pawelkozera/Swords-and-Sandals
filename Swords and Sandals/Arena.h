#pragma once

#include "PlaceInterface.h"
#include "Player.h"
#include "Enemy.h"
#include "GameState.h"
#include "Shop.h"
#include "SoundManager.h"
#include "SaveManager.h"

class Arena : public PlaceInterface
{
private:
	bool playerTurn;
	bool fightInProgress;
	bool playerWon;

	void handleButtonClick(const std::string& buttonName, Player& player, Enemy& enemy, GameState &gameState, TextureManager& textureManager, Shop& shop);
	void handleButtonClickFightInProgress(const std::string& buttonName, Player& player, Enemy& enemy);
	void handleButtonClickFightEnded(const std::string& buttonName, Player& player, Enemy& enemy, GameState& gameState, TextureManager& textureManager, Shop& shop);
	void setUpEndOfFightPositionOfButtons();
public:
	Arena();
	Arena(sf::Texture& arenaTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons(Player& player);
	void checkForClickedButton(const sf::Vector2f& mousePosition, Player& player, Enemy &enemy, GameState& gameState, TextureManager& textureManager, Shop& shop);
	void checkForEndOfFight(Player& player, Enemy& enemy);
	void generatePrize(Player &player);
	void displayEndOfFight(sf::RenderWindow& window);
	void handleEnemyMove(Character &enemy, Player &player);
	const bool getPlayerTurn();
	const bool getFightInProgress();
	void setFightInProgress(bool fightState);
};

