#pragma once

#include "PlaceInterface.h"
#include "GameState.h"
#include "SoundManager.h";
#include "SaveManager.h"

class Settings : public PlaceInterface
{
private:
	int volume;

	void handleButtonClick(const std::string& buttonName, GameState& gameState);
public:
	Settings();
	Settings(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons() override;
	void displayInterface(sf::RenderWindow& window);
	void checkForClickedButton(const sf::Vector2f& mousePosition, GameState& gameState);
	int getVolume();
	void setVolume(int volume);
};

