#include "SaveManager.h"


bool SaveManager::saveCharacterStatsToFile(Player &player) {
    std::ofstream file("Saves/save_stats.txt", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Can not open a file." << std::endl;
        return false;
    }

    file << player.getStrength() << " " << player.getAgility() << " " << player.getAttack() << " " << player.getDefence() << " "
        << player.getVitality() << " " << player.getCharisma() << " " << player.getStamina() << " " << player.getStaminaUsage() << " "
        << player.getAvailablePoints() << " " << player.getGold() << " " << player.getArmor() << " " << player.getHp() << " " << player.getRoundsWin();

    file.close();
    return true;
}

bool SaveManager::loadCharacterStatsFromFile(Player& player) {
    std::ifstream file("Saves/save_stats.txt");
    if (!file.is_open()) {
        std::cerr << "Can not open a file." << std::endl;
        return false;
    }

    int strength, agility, attack, defence, vitality, charisma, stamina, staminaUsage, availablePoints, gold, armor, hp, roundsWin;

    file >> strength >> agility >> attack >> defence >> vitality >> charisma >> stamina >> staminaUsage >> availablePoints >> gold >> armor >> hp >> roundsWin;

    file.close();

    player.setStrength(strength);
    player.setAgility(agility);
    player.setAttack(attack);
    player.setDefence(defence);
    player.setVitality(vitality);
    player.setCharisma(charisma);
    player.setStamina(stamina);
    player.setStaminaUsage(staminaUsage);
    player.setAvailablePoints(availablePoints);
    player.setGold(gold);

    return true;
}

void SaveManager::saveBoughtItemsToFile(Shop& shop) {
    std::ofstream fileArmor("Saves/save_bought_armor.txt", std::ios::trunc);
    if (fileArmor.is_open()) {
        for (const auto& armor : shop.getBoughtArmorPieces()) {
            if (armor.second) {
                fileArmor << armor.first << std::endl;
            }
        }
        fileArmor.close();
    }
    else {
        std::cerr << "Save armor error." << std::endl;
    }

    std::ofstream fileSwords("Saves/save_bought_swords.txt", std::ios::trunc);
    if (fileSwords.is_open()) {
        for (const auto& weapon : shop.getBoughtWeapons()) {
            if (weapon.second) {
                fileSwords << weapon.first << std::endl;
            }
        }
        fileSwords.close();
    }
    else {
        std::cerr << "Save swords error." << std::endl;
    }
}

void SaveManager::loadBoughtItemsFromFile(Shop& shop) {
    std::string itemName;

    std::ifstream fileArmor("Saves/save_bought_armor.txt");
    if (fileArmor.is_open()) {
        while (std::getline(fileArmor, itemName)) {
            if (!itemName.empty()) {
                shop.addBoughtArmorPiece(itemName);
            }
        }

        fileArmor.close();
    }
    else {
        std::cerr << "Error loading armor from file." << std::endl;
    }

    std::ifstream fileWeapons("Saves/save_bought_swords.txt");
    if (fileWeapons.is_open()) {

        while (std::getline(fileWeapons, itemName)) {
            if (!itemName.empty()) {
                shop.addBoughtWeapon(itemName);
            }
        }

        fileWeapons.close();
    }
    else {
        std::cerr << "Error loading weapons from file." << std::endl;
    }
}

void SaveManager::saveEquipedItemsToFile(Shop& shop, Character& player, bool isPlayer) {
    std::string armorFilename = isPlayer ? "Saves/save_equiped_armor_player.txt" : "Saves/save_equiped_armor_enemy.txt";
    std::string weaponFilename = isPlayer ? "Saves/save_equiped_weapon_player.txt" : "Saves/save_equiped_weapon_enemy.txt";

    std::ofstream fileArmor(armorFilename, std::ios::trunc);
    if (player.getEquipedArmor().size() > 0 && fileArmor.is_open()) {
        const std::unordered_multimap<std::string, ArmorPiece>& armorMap = shop.getAvailableArmorPieces();

        for (const auto& armor : armorMap) {
            std::string armorName = armor.second.getName() + armor.second.getType();

            for (const auto& equipedArmor : player.getEquipedArmor()) {
                if (equipedArmor.first == armorName) {
                    fileArmor << armorName << std::endl;
                }
            }
        }

        fileArmor.close();
    }

    std::ofstream fileWeapon(weaponFilename, std::ios::trunc);
    if (player.getEquipedWeapons().size() > 0 && fileWeapon.is_open()) {
        const std::unordered_multimap<std::string, Weapon>& weaponMap = shop.getAvailableWeapons();

        for (const auto& weapon : weaponMap) {
            std::string weaponName = weapon.second.getName() + weapon.second.getType();

            for (const auto& equipedWeapon : player.getEquipedWeapons()) {
                if (equipedWeapon.first == weaponName) {
                    fileWeapon << weaponName << std::endl;
                }
            }
        }

        fileWeapon.close();
    }
    else {
        std::cerr << "Save equiped weapon error." << std::endl;
    }
}

void SaveManager::loadEquipedItemsFromFile(Shop& shop, Character& player, bool isPlayer) {
    std::string armorFilename = isPlayer ? "Saves/save_equiped_armor_player.txt" : "Saves/save_equiped_armor_enemy.txt";
    std::string weaponFilename = isPlayer ? "Saves/save_equiped_weapon_player.txt" : "Saves/save_equiped_weapon_enemy.txt";

    std::string itemName;

    std::ifstream fileArmor(armorFilename);
    if (fileArmor.is_open()) {
        while (std::getline(fileArmor, itemName)) {
            if (!itemName.empty()) {
                const std::unordered_multimap<std::string, ArmorPiece>& armorMap = shop.getAvailableArmorPieces();

                for (const auto& armor : armorMap) {
                    std::string armorName = armor.second.getName() + armor.second.getType();

                    std::string characterPart = armor.first;
                    ArmorPiece newArmor = armor.second;

                    if (itemName == armorName) {
                        player.addArmorPiece(characterPart, newArmor);
                    }
                }

                shop.addBoughtArmorPiece(itemName);
            }
        }

        fileArmor.close();
    }
    else {
        std::cerr << "Error loading equiped armor from file." << std::endl;
    }

    std::ifstream fileWeapon(weaponFilename);
    if (fileWeapon.is_open()) {
        while (std::getline(fileWeapon, itemName)) {
            if (!itemName.empty()) {
                const std::unordered_multimap<std::string, Weapon>& weaponMap = shop.getAvailableWeapons();

                for (const auto& weapon : weaponMap) {
                    std::string weaponName = weapon.second.getName() + weapon.second.getType();

                    std::string characterPart = weapon.first;
                    Weapon newWeapon = weapon.second;

                    if (itemName == weaponName) {
                        if (isPlayer) {
                            player.addWeapon(characterPart, newWeapon);
                        }
                        else {
                            std::string key = "handLeft";
                            player.addWeapon(key, newWeapon);
                        }
                    }
                }

                shop.addBoughtWeapon(itemName);
            }
        }

        fileWeapon.close();
    }
    else {
        std::cerr << "Error loading equiped weapons from file." << std::endl;
    }
}

void SaveManager::saveSettings(int volume) {
    std::ofstream settingsFile("Saves/save_settings.txt", std::ios::trunc);
    if (settingsFile.is_open()) {
        settingsFile << volume;
        settingsFile.close();
    }
    else {
        std::cerr << "Save armor error." << std::endl;
    }
}

int SaveManager::loadSettings() {
    std::ifstream file("Saves/save_settings.txt");
    int volume = 100;

    if (file.is_open()) {
        file >> volume;

        file.close();
    }
    else {
        std::cerr << "Can not open a file." << std::endl;
    }

    return volume;
}

void SaveManager::saveEnemyStatsToFile(Enemy& enemy) {
    std::ofstream file("Saves/save_enemy_stats.txt", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Can not open a file." << std::endl;
    }

    file << enemy.getStrength() << " " << enemy.getAgility() << " " << enemy.getAttack() << " " << enemy.getDefence() << " "
        << enemy.getVitality() << " " << enemy.getCharisma() << " " << enemy.getStamina() << " " << enemy.getStaminaUsage() << " "
        << enemy.getAvailablePoints() << " " << enemy.getArmor() << " " << enemy.getHp();

    file.close();
}

void SaveManager::loadEnemyStatsFromFile(Enemy& enemy) {
    std::ifstream file("Saves/save_enemy_stats.txt");
    if (!file.is_open()) {
        std::cerr << "Can not open a file." << std::endl;
    }

    int strength, agility, attack, defence, vitality, charisma, stamina, staminaUsage, availablePoints, gold, armor, hp;

    file >> strength >> agility >> attack >> defence >> vitality >> charisma >> stamina >> staminaUsage >> availablePoints >> armor >> hp;

    file.close();

    enemy.setStrength(strength);
    enemy.setAgility(agility);
    enemy.setAttack(attack);
    enemy.setDefence(defence);
    enemy.setVitality(vitality);
    enemy.setCharisma(charisma);
    enemy.setStamina(stamina);
    enemy.setStaminaUsage(staminaUsage);
    enemy.setAvailablePoints(availablePoints);
}