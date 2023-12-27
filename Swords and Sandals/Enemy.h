#pragma once

#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
private:
public:
	Enemy() = default;
	Enemy(std::unordered_map<std::string, CharacterPart>& characterPart);

	void generateNewStatsAndEq(Player& player);
};
