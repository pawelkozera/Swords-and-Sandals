#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager
{
private:
    std::unordered_map<std::string, sf::Texture> textures;
public:
    sf::Texture& getTexture(const std::string& textureKey);
    void loadTexture(std::string key, std::string textureSrc);
    void loadCharacterBodyTextures();
};
