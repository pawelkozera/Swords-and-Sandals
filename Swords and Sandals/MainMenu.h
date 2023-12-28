#pragma once

#include "PlaceInterface.h"

class MainMenu : public PlaceInterface
{
private:
public:
	MainMenu();
	MainMenu(sf::Texture& backgroundTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons() override;
};