#pragma once

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "TextureManager.h"

class GameManager {
private:
    sf::RenderWindow window;
public:
    GameManager();
    void run(TextureManager& textureManager);
    std::unordered_map<std::string, CharacterPart> createCharacterPartsMap(TextureManager& textureManager);
    std::unordered_map<std::string, ArmorPiece> createCharacterArmorPieces(TextureManager& textureManager);
};

