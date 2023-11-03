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

void TextureManager::loadButtons() {
    loadTexture("arenaButton", "Assets/Buttons/Arena.png");
    loadTexture("armorerButton", "Assets/Buttons/Armorer.png");
    loadTexture("weaponsmithButton", "Assets/Buttons/Weaponsmith.png");
}

void TextureManager::loadCursor() {
    loadTexture("cursor", "Assets/Cursor/point.png");
}

void TextureManager::loadShop() {
    loadTexture("armorerBackground", "Assets/Shops/armorer.jpg");
    loadTexture("weaponsmithBackground", "Assets/Shops/weaponsmith.jpg");
}