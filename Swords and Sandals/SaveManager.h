#pragma once

#include <ostream>
#include "Player.h"
#include <iostream>
#include <fstream>
#include "Shop.h"
#include "Settings.h"
#include "Enemy.h"

class SaveManager
{
private:
public:
	static bool saveCharacterStatsToFile(Player& player);
	static bool loadCharacterStatsFromFile(Player& player);
	static void saveBoughtItemsToFile(Shop& shop);
	static void loadBoughtItemsFromFile(Shop& shop);
	static void saveEquipedItemsToFile(Shop& shop, Character& player, bool isPlayer);
	static void loadEquipedItemsFromFile(Shop& shop, Character& player, bool isPlayer);
	static void saveSettings(int volume);
	static int loadSettings();
	static void saveEnemyStatsToFile(Enemy& enemy);
	static void loadEnemyStatsFromFile(Enemy& enemy);
};

