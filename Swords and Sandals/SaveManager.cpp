#include "SaveManager.h"


bool SaveManager::saveCharacterStatsToFile(Player &player) {
    std::ofstream file("Saves/save_stats.txt", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Can not open a file." << std::endl;
        return false;
    }

    file << player.getStrength() << " " << player.getAgility() << " " << player.getAttack() << " " << player.getDefence() << " "
        << player.getVitality() << " " << player.getCharisma() << " " << player.getStamina() << " " << player.getStaminaUsage() << " "
        << player.getAvailablePoints() << " " << player.getGold();

    file.close();
    return true;
}

bool SaveManager::loadCharacterStatsFromFile(Player& player) {
    std::ifstream file("Saves/save_stats.txt");
    if (!file.is_open()) {
        std::cerr << "Can not open a file." << std::endl;
        return false;
    }

    int strength, agility, attack, defence, vitality, charisma, stamina, staminaUsage, availablePoints, gold;

    file >> strength >> agility >> attack >> defence >> vitality
        >> charisma >> stamina >> staminaUsage >> availablePoints >> gold;

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

void SaveManager::saveEquipedItemsToFile(Shop& shop, Player& player) {
    std::ofstream fileArmor("Saves/save_equiped_armor.txt", std::ios::trunc);

    if (player.getEquipedArmor().size() > 0) {
        if (fileArmor.is_open()) {
            const std::unordered_multimap<std::string, ArmorPiece>& armorMap = shop.getAvailableArmorPieces();

            for (const auto& armor : armorMap) {
                std::string armorName = armor.second.getName() + armor.second.getType();

                for (const auto& equipedArmor : player.getEquipedArmor()) {
                    if (equipedArmor.first == armorName) {
                        fileArmor << armorName;
                    }
                }
            }

            fileArmor.close();
        }
        else {
            std::cerr << "Save equiped armor error." << std::endl;
        }
    }

    std::ofstream fileWeapon("Saves/save_equiped_weapon.txt", std::ios::trunc);

    if (player.getEquipedWeapons().size() > 0) {
        if (fileWeapon.is_open()) {
            const std::unordered_multimap<std::string, Weapon>& weaponMap = shop.getAvailableWeapons();

            for (const auto& weapon : weaponMap) {
                std::string weaponName = weapon.second.getName() + weapon.second.getType();

                for (const auto& equipedWeapon : player.getEquipedWeapons()) {
                    if (equipedWeapon.first == weaponName) {
                        fileWeapon << weaponName;
                    }
                }
            }

            fileWeapon.close();
        }
        else {
            std::cerr << "Save equiped weapon error." << std::endl;
        }
    }
}

void SaveManager::loadEquipedItemsFromFile(Shop& shop, Player& player) {
    std::string itemName;

    std::ifstream fileArmor("Saves/save_equiped_armor.txt");
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

    std::ifstream fileWeapon("Saves/save_equiped_weapon.txt");
    if (fileWeapon.is_open()) {
        while (std::getline(fileWeapon, itemName)) {
            if (!itemName.empty()) {
                const std::unordered_multimap<std::string, Weapon>& weaponMap = shop.getAvailableWeapons();

                for (const auto& weapon : weaponMap) {
                    std::string weaponName = weapon.second.getName() + weapon.second.getType();

                    std::string characterPart = weapon.first;
                    Weapon newWeapon = weapon.second;

                    if (itemName == weaponName) {
                        player.addWeapon(characterPart, newWeapon);
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