#pragma once

#include "Character.h"

class Player : public Character
{
private:
	int strength;
	int agility;
	int attack;
	int defence;
	int vitality;
	int charisma;
	int stamina;
	int gold;

	std::unordered_multimap<std::string, ArmorPiece> equipedArmorPieces;
	std::unordered_multimap<std::string, ArmorPiece> equipedWeapons;
public:
	Player() = default;
	Player(std::unordered_map<std::string, CharacterPart>& characterPart);
	const int getGold();
	void buy(int gold);
};

