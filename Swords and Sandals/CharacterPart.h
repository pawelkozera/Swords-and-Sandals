#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class CharacterPart
{
private:
	sf::Sprite sprite;
	sf::Vector2f position;
	float scaleX, scaleY;
public:
	CharacterPart(const sf::Texture& texture);
	sf::Sprite const getSprite() const;
	sf::Vector2f const getPosition() const;
	sf::FloatRect const getSpriteSize() const;
	void setPosition(const sf::Vector2f position);
	void flipSprite();
};

