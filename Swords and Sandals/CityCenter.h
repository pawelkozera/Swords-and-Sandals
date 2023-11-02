#pragma once

#include <SFML/Graphics.hpp>

class CityCenter
{
private:
	sf::Sprite citySprite;
public:
	CityCenter(sf::Texture &cityTexture);
	const sf::Sprite getSprite() const;
};

