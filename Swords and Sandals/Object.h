#pragma once

#include <SFML/Graphics.hpp>


class Object
{
private:
	sf::Sprite sprite;
	sf::Vector2f position;
	float scaleX, scaleY;
public:
	Object(const sf::Texture& texture);
	sf::Sprite const getSprite() const;
	sf::Vector2f const getPosition() const;
	sf::FloatRect const getSpriteRect() const;
	void setPosition(const sf::Vector2f position);
	void flipSprite();
};

