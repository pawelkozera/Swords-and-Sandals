#pragma once

#include "Object.h"
#include "Item.h"

class ArmorPiece : public Object, public Item
{
private:
	int defence;
	std::string type;
public:
	ArmorPiece(const sf::Texture& texture, int defence, int price, std::string name, std::string type);
	const bool isClicked(const sf::Vector2f& mousePosition) const;
	const int getDefence() const;
	const std::string getType() const;
};

