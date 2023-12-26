#pragma once

#include "PlaceInterface.h"
#include "GameState.h"
#include "Player.h"
#include "Arena.h"


class ArenaEntrance : public PlaceInterface 
{
private:
public:
	ArenaEntrance();
	ArenaEntrance(sf::Texture& backgroundTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons() override;
	void checkForClickedButton(const sf::Vector2f& mousePosition, GameState &gameState, Player& player, Character& enemy, Arena& arena);
	void handleButtonClick(const std::string& buttonName, GameState& gameState, Player& player, Character& enemy, Arena& arena);
	void displayInterface(sf::RenderWindow& window, Player& player, Character& enemy);
};

