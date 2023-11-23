#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class PlayerInterface
{
private:
	sf::Sprite sprite;
public:
	PlayerInterface();
	PlayerInterface(sf::Texture& texture);

	void displayInterface(sf::RenderWindow& window, Player& player);
};

