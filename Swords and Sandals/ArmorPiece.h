#pragma once

#include "Object.h"

class ArmorPiece : public Object
{
private:
	int defence;
public:
	ArmorPiece(const sf::Texture& texture);
	const bool isClicked(const sf::Vector2f& mousePosition) const;
};

