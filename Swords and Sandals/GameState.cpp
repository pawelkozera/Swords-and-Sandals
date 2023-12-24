#include "GameState.h"


GameState::GameState() : currentMode(GameMode::InCity) {}

void GameState::setMode(GameMode mode) {
    currentMode = mode;
}

bool GameState::isMainMenu() const {
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

bool GameState::InCreationMenu() const
{
    return currentMode == GameMode::InCreationMenu;
}
