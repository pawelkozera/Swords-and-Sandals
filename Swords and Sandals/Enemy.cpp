#include "Enemy.h"


Enemy::Enemy(std::unordered_map<std::string, CharacterPart>& characterPart)
    : Character(characterPart)
{
}

void Enemy::generateNewStatsAndEq(Player& player, TextureManager& textureManager) {
    static std::random_device rd;
    static std::mt19937 generator(rd());

	std::unordered_multimap<std::string, ArmorPiece> armorMap = createArmorMap(textureManager);

    std::uniform_int_distribution<int> armorDistribution(-1, 1);
    int amountOfArmorPieces = player.getArmorSize() + armorDistribution(generator);

    for (int i = 0; i < amountOfArmorPieces; i++) {
        std::uniform_int_distribution<int> armorIndexDistribution(0, armorMap.size() - 1);
        int randomIndex = armorIndexDistribution(generator);

        auto it = std::next(armorMap.begin(), randomIndex);
        
        std::string armorKey = it->first;
        addArmorPiece(armorKey, it->second);

        armorMap.erase(it);
    }

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
		std::uniform_int_distribution<int> statsDistribution(0, 6);
		whichStatistics = statsDistribution(generator);

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

std::unordered_multimap<std::string, ArmorPiece> Enemy::createArmorMap(TextureManager& textureManager) {
    std::unordered_multimap<std::string, ArmorPiece> availableArmorPieces;

    availableArmorPieces.insert({ "head", ArmorPiece(textureManager.getTexture("DKAhead"), 1, 200, "Dark knight", "helmet") });
    availableArmorPieces.insert({ "chest", ArmorPiece(textureManager.getTexture("DKAchest"), 1, 500, "Dark knight", "breastplate") });

    availableArmorPieces.insert({ "shoulderLeft", ArmorPiece(textureManager.getTexture("DKAshoulder"), 1, 300, "Dark knight", "shoulderguard left") });

    ArmorPiece DKAshoulderRight(textureManager.getTexture("DKAshoulder"), 1, 300, "Dark knight", "shoulderguard right");
    DKAshoulderRight.flipSprite();
    availableArmorPieces.insert({ "shoulderRight", DKAshoulderRight });

    availableArmorPieces.insert({ "elbowLeft", ArmorPiece(textureManager.getTexture("DKAelbow"), 1, 300, "Dark knight", "gauntlet left") });

    ArmorPiece DKAeblowRight(textureManager.getTexture("DKAelbow"), 1, 300, "Dark knight", "gauntlet right");
    DKAeblowRight.flipSprite();
    availableArmorPieces.insert({ "elbowRight", DKAeblowRight });

    availableArmorPieces.insert({ "armLeft", ArmorPiece(textureManager.getTexture("DKAarm"), 1, 300, "Dark knight", "glove left") });

    ArmorPiece DKAarmRight(textureManager.getTexture("DKAarm"), 1, 300, "Dark knight", "glove right");
    DKAarmRight.flipSprite();
    availableArmorPieces.insert({ "armRight",  DKAarmRight });

    availableArmorPieces.insert({ "pelvis", ArmorPiece(textureManager.getTexture("DKApelvis"), 1, 300, "Dark knight", "pants") });

    availableArmorPieces.insert({ "thighLeft", ArmorPiece(textureManager.getTexture("DKAthigh"), 1, 300, "Dark knight", "greave left") });

    ArmorPiece DKAthighRight(textureManager.getTexture("DKAthigh"), 1, 300, "Dark knight", "greave right");
    DKAthighRight.flipSprite();
    availableArmorPieces.insert({ "thighRight",  DKAthighRight });

    availableArmorPieces.insert({ "legLeft", ArmorPiece(textureManager.getTexture("DKAleg"), 1, 300, "Dark knight", "shinguard left") });

    ArmorPiece DKAlegRight(textureManager.getTexture("DKAleg"), 1, 300, "Dark knight", "shinguard right");
    DKAlegRight.flipSprite();
    availableArmorPieces.insert({ "legRight",  DKAlegRight });

    availableArmorPieces.insert({ "footLeft", ArmorPiece(textureManager.getTexture("DKAfoot"), 1, 300, "Dark knight", "boot left") });

    ArmorPiece DKAfootRight(textureManager.getTexture("DKAfoot"), 1, 300, "Dark knight", "boot right");
    DKAfootRight.flipSprite();
    availableArmorPieces.insert({ "footRight",  DKAfootRight });

    return availableArmorPieces;
}