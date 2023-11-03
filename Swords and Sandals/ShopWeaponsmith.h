#pragma once

#include "Shop.h"

class ShopWeaponsmith : public Shop
{
private:

public:
	ShopWeaponsmith(const sf::Texture& backgroundTexture, const std::vector<Button>& buttons);
};

