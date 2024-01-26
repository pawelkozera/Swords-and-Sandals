#include "Item.h"

Item::Item(std::string name, int price) {
	this->price = price;
	this->name = name;
}

const int Item::getPrice() const
{
	return price;
}

const std::string Item::getName() const
{
	return name;
}