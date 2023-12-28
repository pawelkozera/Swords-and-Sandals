#pragma once

#include "Character.h"

class Player : public Character
{
private:
	int gold;
public:
	Player() = default;
	Player(std::unordered_map<std::string, CharacterPart>& characterPart);
	void buy(int gold);
	const int getGold();
	void setGold(const int gold);
	void addGold(const int gold);
};

