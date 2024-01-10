#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "Button.h"
#include "CityCenter.h"
#include "GameState.h"
#include "Cursor.h"
#include "Shop.h"
#include <functional>
#include "PlayerInterface.h"
#include "PlayerCreation.h"
#include "Arena.h"
#include "ArenaEntrance.h"
#include "MainMenu.h"
#include "Settings.h"

class GameManager {
private:
    sf::RenderWindow window;
    Enemy enemy;
    Player player;
    CityCenter cityCenter;
    GameState gameState;
    TextureManager textureManager;
    Cursor cursor;
    Shop shop;
    PlayerInterface playerInterface;
    PlayerCreation playerCreation;
    Arena arena;
    ArenaEntrance arenaEntrance;
    MainMenu mainMenu;
    Settings settings;

    std::unordered_map<std::string, std::function<void()>> buttonHandlers;

    const float targetFPS = 60.0f;
    const sf::Time timePerFrame = sf::seconds(1.0f / targetFPS);
public:
    GameManager(TextureManager &textureManager);
    void run();
    void setUp();
    void handleEvents();
    void handleMainMenuEvents();
    void handleShopEvents();
    void handleArenaEvents();
    void handleArenaEntranceEvents();
    void handlePlayerCreationEvents();
    void handleSettingsEvents();
    void handleCityCenterButtons();
    void handleShopButtons();
    std::unordered_map<std::string, CharacterPart> createCharacterPartsMap();
    std::unordered_map<std::string, ArmorPiece> createCharacterArmorPieces();
    std::unordered_map<std::string, Button> createCityCenterButtonsMap();
    std::unordered_map<std::string, Button> createArenaButtonsMap();
    std::unordered_map<std::string, Button> createArenaEntranceButtonsMap();
    std::unordered_map<std::string, Button> createShopButtonsMap();
    std::unordered_map<std::string, Button> createPlayerCreationButtonsMap();
    std::unordered_map<std::string, Button> createMainMenuButtonsMap();
    std::unordered_map<std::string, Button> createSettingsButtonsMap();
};

