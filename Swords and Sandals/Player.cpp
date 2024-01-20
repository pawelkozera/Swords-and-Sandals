#include "Player.h"

Player::Player(std::unordered_map<std::string, CharacterPart>& characterPart)
    : Character(characterPart), gold(300), roundsWin(0)
{
}

void Player::buy(int gold) {
    this->gold -= gold;
}

const int Player::getGold() {
    return gold;
}

void Player::setGold(const int gold) {
    this->gold = gold;
}

void Player::addGold(const int gold) {
    this->gold += gold;
}

const int Player::getRoundsWin() {
    return roundsWin;
}

void Player::increaseRoundsWin() {
    roundsWin++;
}

void Player::resetRoundsWin() {
    roundsWin = 0;
}