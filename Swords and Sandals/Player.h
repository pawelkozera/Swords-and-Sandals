#pragma once

#include "Character.h"

class Player : public Character
{
private:
	std::unordered_multimap<std::string, ArmorPiece> equipedArmorPieces;
	std::unordered_multimap<std::string, ArmorPiece> equipedWeapons;
	int gold;
public:
	Player() = default;
	Player(std::unordered_map<std::string, CharacterPart>& characterPart);
	void buy(int gold);
	const int getGold();
};

