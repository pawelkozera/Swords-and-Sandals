#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Button.h"
#include "PlaceInterface.h"

class CityCenter : public PlaceInterface
{
private:
public:
	CityCenter();
	CityCenter(sf::Texture &cityTexture, std::unordered_map<std::string, Button> & buttons);
	void setUpPositionOfButtons() override;
};

