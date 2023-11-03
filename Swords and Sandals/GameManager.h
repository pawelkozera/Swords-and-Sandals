#pragma once

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "TextureManager.h"
#include "Button.h"
#include "CityCenter.h"
#include "GameState.h"

class GameManager {
private:
    sf::RenderWindow window;
    Character character;
    CityCenter cityCenter;
    GameState gameState;
    TextureManager textureManager;
public:
    GameManager(TextureManager &textureManager);
    void run();
    void setUp();
    std::unordered_map<std::string, CharacterPart> createCharacterPartsMap();
    std::unordered_map<std::string, ArmorPiece> createCharacterArmorPieces();
    std::unordered_map<std::string, Button> createCityCenterButtonsMap();
};

