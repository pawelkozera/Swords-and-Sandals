#pragma once

#include "Object.h"
#include "Item.h"

class Weapon : public Object, public Item
{
private:
	int attack;
	int price;
	std::string name;
	std::string type;
public:
	Weapon(const sf::Texture& texture, int attack, int price, std::string name, std::string type);
	const bool isClicked(const sf::Vector2f& mousePosition) const;
	const int getAttack() const;
	const std::string getType() const;
};

