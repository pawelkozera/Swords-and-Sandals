#pragma once

#include "PlaceInterface.h"

class Settings : public PlaceInterface
{
private:
	int volume;
public:
	Settings();
	Settings(sf::Texture& cityTexture, std::unordered_map<std::string, Button>& buttons);
	void setUpPositionOfButtons() override;
};

