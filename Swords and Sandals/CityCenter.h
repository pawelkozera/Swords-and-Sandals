#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Button.h"

class CityCenter
{
private:
	sf::Sprite citySprite;
	std::unordered_map<std::string, Button> buttons;
public:
	CityCenter();
	CityCenter(sf::Texture &cityTexture, std::unordered_map<std::string, Button> & buttons);
	const sf::Sprite getSprite() const;
	void displayButtons(sf::RenderWindow &window);
	void displayCity(sf::RenderWindow &window);
	void setUpPositionOfButtons();
	const Button getButton(const std::string &buttonName) const;
};

