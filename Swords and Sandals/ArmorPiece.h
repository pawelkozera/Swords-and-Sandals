#pragma once

#include "Object.h"

class ArmorPiece : public Object
{
private:
	int defence;
	int price;
public:
	ArmorPiece(const sf::Texture& texture, int defence, int price);
	const bool isClicked(const sf::Vector2f& mousePosition) const;
	const int getDefence() const;
	const int getPrice() const;
};

