#include "CityCenter.h"


CityCenter::CityCenter(sf::Texture &cityTexture) {
	citySprite.setTexture(cityTexture);
	citySprite.setPosition(0.0f, -30.0f);
}

const sf::Sprite CityCenter::getSprite() const {
	return citySprite;
}