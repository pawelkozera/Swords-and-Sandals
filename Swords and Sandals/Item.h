#pragma once

#include <string>

class Item
{
private:
	int price;
	std::string name;
public:
	Item(std::string name, int price);
	const int getPrice() const;
	const std::string getName() const;
};

