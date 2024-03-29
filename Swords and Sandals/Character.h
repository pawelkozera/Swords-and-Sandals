#pragma once

#include <unordered_map>
#include <random>

#include "CharacterPart.h"
#include "ArmorPiece.h"
#include "Weapon.h"
#include "SoundManager.h"

class Character
{
private:
	static std::random_device rd;

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
	int staminaUsage;
	int availablePoints;
	int hp;
	int armor;

	bool animationRunning;

	std::unordered_map<std::string, bool> equipedArmor;
	std::unordered_map<std::string, bool> equipedWeapons;

	void resetPart(const std::string& partName);
	void rotateAndMovePart(const std::string& partName, float angle, const sf::Vector2f& moveCharacter, const sf::Vector2f& moveArmor);
public:
	Character();
	Character(std::unordered_map<std::string, CharacterPart> &characterParts);
	void assembleBody();
	void updateArmorAndWeaponPositions();
	void walkAnimation();
	void attackAnimation(bool rightHand);
	void restAnimation();
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
	int rollDice(int min, int max);
	void resetStatsAndEq();
	void restoreArmor();
	int getReach();
	int getSpeed();
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
	void setHp(int hp);
	void setStaminaUsage(int newStamina);
	void setStrength(int strength);
	void setAgility(int agility);
	void setAttack(int attack);
	void setDefence(int defence);
	void setVitality(int vitality);
	void setCharisma(int charisma);
	void setStamina(int stamina);
	void setAvailablePoints(int availablePoints);
	void takeDamage(int damage);
	const int getStrength();
	const int getAgility();
	const int getAttack();
	const int getDefence();
	const int getVitality();
	const int getCharisma();
	const int getStamina();
	const int getHp();
	const int getStaminaUsage();
	const int getAvailablePoints();
	const sf::Vector2f getBodyPosition();
	const bool getAnimationRunning();
	const int getArmorSize();
	const int getArmor();
	std::unordered_map<std::string, bool> getEquipedArmor();
	std::unordered_map<std::string, bool> getEquipedWeapons();
	void setStaminaUsageAndHp();
};

