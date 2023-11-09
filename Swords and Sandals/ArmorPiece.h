#pragma once

#include "Object.h"

class ArmorPiece : public Object
{
private:
	int defence;
	int price;
	std::string name;
	std::string type;
public:
	ArmorPiece(const sf::Texture& texture, int defence, int price, std::string name, std::string type);
	const bool isClicked(const sf::Vector2f& mousePosition) const;
	const int getDefence() const;
	const int getPrice() const;
	const std::string getName() const;
	const std::string getType() const;
};

