#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TextureManager.h"
#include "Button.h"
#include "CityCenter.h"
#include "GameState.h"
#include "Cursor.h"
#include "Shop.h"
#include <functional>

class GameManager {
private:
    sf::RenderWindow window;
    Character character;
    Player player;
    CityCenter cityCenter;
    GameState gameState;
    TextureManager textureManager;
    Cursor cursor;
    Shop shop;

    std::unordered_map<std::string, std::function<void()>> buttonHandlers;
public:
    GameManager(TextureManager &textureManager);
    void run();
    void setUp();
    void handleEvents();
    void handleShopEvents();
    void handleCityCenterButtons();
    void handleShopButtons();
    std::unordered_map<std::string, CharacterPart> createCharacterPartsMap();
    std::unordered_map<std::string, ArmorPiece> createCharacterArmorPieces();
    std::unordered_map<std::string, Button> createCityCenterButtonsMap();
    std::unordered_map<std::string, Button> createShopButtonsMap();
};

