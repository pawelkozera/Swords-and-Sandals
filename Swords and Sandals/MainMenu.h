#pragma once

#include "PlaceInterface.h"
#include "Enemy.h"
#include "Player.h"
#include "GameState.h"
#include "Shop.h"

class MainMenu : public PlaceInterface
{
private:
	void handleButtonClick(const std::string& buttonName, Player& player, Enemy& enemy, GameState& gameState, TextureManager& textureManager, Shop& shop);
public:
	MainMenu();
	MainMenu(sf::Texture& backgroundTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons() override;
	void checkForClickedButton(const sf::Vector2f& mousePosition, Player& player, Enemy& enemy, GameState& gameState, TextureManager& textureManager, Shop& shop);
};