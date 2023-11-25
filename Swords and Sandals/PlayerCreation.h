#pragma once

#include "PlaceInterface.h"
#include "Player.h"
#include "GameState.h"

class PlayerCreation : public PlaceInterface
{
private:
	void handleButtonClick(const std::string& buttonName, Player& player, GameState& gameState);
	void handlePlusButtonClick(const std::string& buttonName, Player& player);
	void handleMinusButtonClick(const std::string& buttonName, Player& player);
public:
	PlayerCreation();
	PlayerCreation(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons() override;
	void displayInterface(sf::RenderWindow&window, Player &player);
	void checkForClickedButton(const sf::Vector2f& mousePosition, Player &player, GameState &gameState);
};

