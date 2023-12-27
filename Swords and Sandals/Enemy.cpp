#include "Enemy.h"


Enemy::Enemy(std::unordered_map<std::string, CharacterPart>& characterPart)
    : Character(characterPart)
{
}

void Enemy::generateNewStatsAndEq(Player& player) {
    static std::random_device rd;
    static std::mt19937 generator(rd());

	int playerModifiedAttributes[7] = {
		player.getStrength(),
		player.getAgility(),
		player.getAttack(),
		player.getDefence(),
		player.getVitality(),
		player.getCharisma(),
		player.getStamina()
	};

	int availablePoints = player.getAvailablePoints() + 4;

	int whichStatistics = 0;
	for (int i = 0; i < availablePoints; i++) {
		std::uniform_int_distribution<int> distribution(0, 6);
		whichStatistics = distribution(generator);

		playerModifiedAttributes[whichStatistics] += 1;
	}

	setStrength(playerModifiedAttributes[0]);
	setAgility(playerModifiedAttributes[1]);
	setAttack(playerModifiedAttributes[2]);
	setDefence(playerModifiedAttributes[3]);
	setVitality(playerModifiedAttributes[4]);
	setCharisma(playerModifiedAttributes[5]);
	setStamina(playerModifiedAttributes[6]);
	setHp(10 + playerModifiedAttributes[4] * 2);
}