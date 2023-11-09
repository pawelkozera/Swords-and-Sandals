#pragma once

#include <unordered_map>

#include "CharacterPart.h"
#include "ArmorPiece.h"

class Character
{
private:
	std::unordered_map<std::string, CharacterPart> characterParts;
	std::unordered_map<std::string, ArmorPiece> armorPieces;
public:
	Character();
	Character(std::unordered_map<std::string, CharacterPart> &characterParts);
	void assembleBody();
	void updateArmorPositions();
	void display(sf::RenderWindow& window);
};

