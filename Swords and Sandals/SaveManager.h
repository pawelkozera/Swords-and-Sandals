#pragma once

#include <ostream>
#include "Player.h"
#include <iostream>
#include <fstream>
#include "Shop.h"

class SaveManager
{
private:
public:
	static bool saveCharacterStatsToFile(Player& player);
	static bool loadCharacterStatsFromFile(Player& player);
	static void saveBoughtItemsToFile(Shop& shop);
	static void loadBoughtItemsFromFile(Shop& shop);
	static void saveEquipedItemsToFile(Shop& shop, Player& player);
	static void loadEquipedItemsFromFile(Shop& shop, Player& player);
};

