#include "TextureManager.h"

TextureManager::TextureManager()
{
}

sf::Texture& TextureManager::getTexture(const std::string& textureKey) {
    if (textures.find(textureKey) == textures.end()) {
        sf::Texture texture;
        if (texture.loadFromFile(textureKey)) {
            textures[textureKey] = texture;
        }
        else {
            throw std::runtime_error("Failed to load " + textureKey);
        }
    }

    return textures[textureKey];
}

void TextureManager::loadTexture(std::string key, std::string textureSrc) {
    if (textures.find(key) != textures.end()) {
        throw std::runtime_error("Texture with key " + key + " already exists");
    }

    sf::Texture texture;

    if (texture.loadFromFile(textureSrc)) {
        textures.insert_or_assign(key, texture);
    }
    else {
        throw std::runtime_error("Failed to load " + textureSrc);
    }
}

void TextureManager::loadCharacterBodyTextures() {
    loadTexture("head", "Assets/Body/BodyHeadEyesOpened.png");
    loadTexture("chest", "Assets/Body/BodyChest.png");
    loadTexture("shoulder", "Assets/Body/BodyShoulderLeft.png");
    loadTexture("elbow", "Assets/Body/BodyElbowLeft.png");
    loadTexture("arm", "Assets/Body/BodyArm.png");
    loadTexture("pelvis", "Assets/Body/BodyPelvis.png");
    loadTexture("thigh", "Assets/Body/BodyThigh.png");
    loadTexture("leg", "Assets/Body/BodyLeg.png");
    loadTexture("foot", "Assets/Body/BodyFoot.png");
}

void TextureManager::loadDarkKnightArmor() {
    loadTexture("DKAhead", "Assets/Armor/DarkKnightArmorHead.png");
    loadTexture("DKAchest", "Assets/Armor/DarkKnightArmorChest.png");
    loadTexture("DKAshoulder", "Assets/Armor/DarkKnightArmorShoulder.png");
    loadTexture("DKAelbow", "Assets/Armor/DarkKnightArmorElbow.png");
    loadTexture("DKAarm", "Assets/Armor/DarkKnightArmorArm.png");
    loadTexture("DKApelvis", "Assets/Armor/DarkKnightArmorPelvis.png");
    loadTexture("DKAthigh", "Assets/Armor/DarkKnightArmorThigh.png");
    loadTexture("DKAleg", "Assets/Armor/DarkKnightArmorLeg.png");
    loadTexture("DKAfoot", "Assets/Armor/DarkKnightArmorFoot.png");
}

void TextureManager::loadCityCenter() {
    loadTexture("cityCenter", "Assets/City/cityCenter.jpg");
}

void TextureManager::loadArena() {
    loadTexture("arena", "Assets/Arena/background.png");
}

void TextureManager::loadButtons() {
    loadTexture("arenaButton", "Assets/Buttons/Arena.png");
    loadTexture("armorerButton", "Assets/Buttons/Armorer.png");
    loadTexture("weaponsmithButton", "Assets/Buttons/Weaponsmith.png");
    loadTexture("backButton", "Assets/Buttons/Back.png");
    loadTexture("buyButton", "Assets/Buttons/Buy.png");
    loadTexture("equipButton", "Assets/Buttons/Equip.png");
    loadTexture("unequipButton", "Assets/Buttons/Unequip.png");
    loadTexture("plusButton", "Assets/Buttons/Plus.png");
    loadTexture("minusButton", "Assets/Buttons/Minus.png");
    loadTexture("goToCityButton", "Assets/Buttons/City.png");
    loadTexture("characterCreation", "Assets/Buttons/Character.png");
    loadTexture("movePlayerForward", "Assets/Buttons/movePlayerForward.png");
    loadTexture("movePlayerBackwards", "Assets/Buttons/movePlayerBackwards.png");
    loadTexture("attackPlayer", "Assets/Buttons/attackPlayer.png");
    loadTexture("restPlayer", "Assets/Buttons/restPlayer.png");
}

void TextureManager::loadCursor() {
    loadTexture("cursor", "Assets/Cursor/point.png");
}

void TextureManager::loadShop() {
    loadTexture("armorerBackground", "Assets/Shops/armorer.jpg");
    loadTexture("weaponsmithBackground", "Assets/Shops/weaponsmith.jpg");
    loadTexture("armIcon", "Assets/UI/Arm_Icon.png");
    loadTexture("calfIcon", "Assets/UI/Calf_Icon.png");
    loadTexture("chestIcon", "Assets/UI/Chest_Icon.png");
    loadTexture("feetIcon", "Assets/UI/Feet_Icon.png");
    loadTexture("forearm_icon", "Assets/UI/Forearm_Icon.png");
    loadTexture("hemletIcon", "Assets/UI/Helmet_Icon.png");
    loadTexture("pantsIcon", "Assets/UI/Pants_Icon.png");
    loadTexture("shoulderIcon", "Assets/UI/Shoulder_Icon.png");
    loadTexture("swordIcon", "Assets/UI/Sword_Icon.png");
    loadTexture("thighIcon", "Assets/UI/Thigh_Icon.png");

    loadTexture("coinIcon", "Assets/UI/Coin_Icon.png");
}

void TextureManager::loadSwords() {
    loadTexture("blueSword", "Assets/Swords/blueSword.png");
}

void TextureManager::loadPlayerCreation() {
    loadTexture("playerCreationBackground", "Assets/PlayerCreation/background.jpg");
}
