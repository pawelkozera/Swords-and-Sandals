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
    gold(900)
{
}

const int Player::getGold() {
    return gold;
}

void Player::buy(int gold) {
    this->gold -= gold;
}