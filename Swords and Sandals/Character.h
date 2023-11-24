#pragma once

#include <unordered_map>

#include "CharacterPart.h"
#include "ArmorPiece.h"
#include "Weapon.h"

class Character
{
private:
	std::unordered_map<std::string, CharacterPart> characterParts;
	std::unordered_map<std::string, ArmorPiece> armorPieces;
	std::unordered_map<std::string, Weapon> weapons;
public:
	Character();
	Character(std::unordered_map<std::string, CharacterPart> &characterParts);
	void assembleBody();
	void updateArmorPositions();
	void display(sf::RenderWindow& window);
	void addArmorPiece(std::string& characterPart, ArmorPiece& armorPiece);
	void addWeapon(std::string& characterPart, Weapon& weapon);
	bool isArmorPieceInMap(ArmorPiece* armorPiece) const;
	bool isWeaponInMap(Weapon* armorPiece) const;
	void removeArmorPiece(const std::string &characterPart);
	void removeWeapon(const std::string &characterPart);
};

