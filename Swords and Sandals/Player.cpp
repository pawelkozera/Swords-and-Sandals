#include "Player.h"

Player::Player(std::unordered_map<std::string, CharacterPart>& characterPart)
    : Character(characterPart),
    strength(1),
    agility(1),
    attack(1),
    defence(1),
    vitality(1),
    charisma(1),
    stamina(1),
    availablePoints(99),
    gold(900)
{
}

const int Player::getGold() {
    return gold;
}

const int Player::getStrength()
{
    return strength;
}

const int Player::getAgility()
{
    return agility;
}

const int Player::getAttack()
{
    return attack;
}

const int Player::getDefence()
{
    return defence;
}

const int Player::getVitality()
{
    return vitality;
}

const int Player::getCharisma()
{
    return charisma;
}

const int Player::getStamina()
{
    return stamina;
}

const int Player::getAvailablePoints()
{
    return availablePoints;
}

void Player::addAvailablePoints(int amount) {
    availablePoints += amount;
}

void Player::buy(int gold) {
    this->gold -= gold;
}

void Player::incrementStrength() {
    strength++;
}

void Player::decrementStrength() {
    strength--;
}

void Player::incrementAgility() {
    agility++;
}

void Player::decrementAgility() {
    agility--;
}

void Player::incrementAttack() {
    attack++;
}

void Player::decrementAttack() {
    attack--;
}

void Player::incrementDefence() {
    defence++;
}

void Player::decrementDefence() {
    defence--;
}

void Player::incrementVitality() {
    vitality++;
}

void Player::decrementVitality() {
    vitality--;
}

void Player::incrementCharisma() {
    charisma++;
}

void Player::decrementCharisma() {
    charisma--;
}

void Player::incrementStamina() {
    stamina++;
}

void Player::decrementStamina() {
    stamina--;
}