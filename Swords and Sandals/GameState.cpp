#include "GameState.h"


GameState::GameState() : currentMode(GameMode::MainMenu) {}

void GameState::setMode(GameMode mode) {
    currentMode = mode;
}

bool GameState::InMainMenu() const {
    return currentMode == GameMode::MainMenu;
}

GameState::GameMode GameState::getMode() const {
    return currentMode;
}

bool GameState::isInCity() const {
    return currentMode == GameMode::InCity;
}

bool GameState::InWeaponsmithShop() const {
    return currentMode == GameMode::InWeaponsmithShop;
}

bool GameState::InArmorerShop() const {
    return currentMode == GameMode::InArmorerShop;
}

bool GameState::InArena() const {
    return currentMode == GameMode::InArena;
}

bool GameState::InArenaEntrance() const {
    return currentMode == GameMode::InArenaEntrance;
}

bool GameState::InCreationMenu() const {
    return currentMode == GameMode::InCreationMenu;
}

bool GameState::InSettings() const {
    return currentMode == GameMode::InSettings;
}