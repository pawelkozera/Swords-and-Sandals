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
	int availablePoints;
	int gold;

	std::unordered_multimap<std::string, ArmorPiece> equipedArmorPieces;
	std::unordered_multimap<std::string, ArmorPiece> equipedWeapons;
public:
	Player() = default;
	Player(std::unordered_map<std::string, CharacterPart>& characterPart);
	const int getGold();
	const int getStrength();
	const int getAgility();
	const int getAttack();
	const int getDefence();
	const int getVitality();
	const int getCharisma();
	const int getStamina();
	const int getAvailablePoints();
	void addAvailablePoints(int amount);
	void buy(int gold);
	void incrementStrength();
	void decrementStrength();
	void incrementAgility();
	void decrementAgility();
	void incrementAttack();
	void decrementAttack();
	void incrementDefence();
	void decrementDefence();
	void incrementVitality();
	void decrementVitality();
	void incrementCharisma();
	void decrementCharisma();
	void incrementStamina();
	void decrementStamina();
};

