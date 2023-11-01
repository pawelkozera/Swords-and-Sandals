#include "TextureManager.h"

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