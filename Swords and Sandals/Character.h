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
	sf::Vector2f bodyPosition;

	int strength;
	int agility;
	int attack;
	int defence;
	int vitality;
	int charisma;
	int stamina;
	int availablePoints;

	bool animationRunning;
public:
	Character();
	Character(std::unordered_map<std::string, CharacterPart> &characterParts);
	void assembleBody();
	void updateArmorPositions();
	void walkAnimation();
	void resetAnimation();
	void moveBody(sf::Vector2f movePosition);
	void setBodyPosition(sf::Vector2f bodyPosition);
	void display(sf::RenderWindow& window);
	void addArmorPiece(std::string& characterPart, ArmorPiece& armorPiece);
	void addWeapon(std::string& characterPart, Weapon& weapon);
	bool isArmorPieceInMap(ArmorPiece* armorPiece) const;
	bool isWeaponInMap(Weapon* armorPiece) const;
	void removeArmorPiece(const std::string &characterPart);
	void removeWeapon(const std::string &characterPart);
	void attackEnemy(Character &enemy);
	void rest();
	void addAvailablePoints(int amount);
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
	const int getStrength();
	const int getAgility();
	const int getAttack();
	const int getDefence();
	const int getVitality();
	const int getCharisma();
	const int getStamina();
	const int getAvailablePoints();
	const sf::Vector2f getBodyPosition();
	const bool getAnimationRunning();
};

