#pragma once

#include "Character.h"
#include "Player.h"
#include "TextureManager.h"

class Enemy : public Character
{
private:
	std::unordered_multimap<std::string, ArmorPiece> createArmorMap(TextureManager &textureManager);
	std::unordered_multimap<std::string, Weapon> createWeaponMap(TextureManager& textureManager);
	void generateStats(Player &player);
	void generateArmor(Player& player, TextureManager &textureManager);
	void generateWeapon(Player& player, TextureManager &textureManager);
public:
	Enemy() = default;
	Enemy(std::unordered_map<std::string, CharacterPart>& characterPart);

	void generateNewStatsAndEq(Player& player, TextureManager& textureManager);
};
