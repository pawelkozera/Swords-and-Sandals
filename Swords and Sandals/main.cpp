#include "GameManager.h"
#include "TextureManager.h"

int main() {
    TextureManager textureManager;

    textureManager.loadCharacterBodyTextures();
    textureManager.loadDarkKnightArmor();
    textureManager.loadCityCenter();
    textureManager.loadArena();
    textureManager.loadButtons();
    textureManager.loadCursor();
    textureManager.loadShop();
    textureManager.loadSwords();
    textureManager.loadPlayerCreation();
    textureManager.loadMainMenu();

    GameManager gameManager(textureManager);

    gameManager.run();

    return 0;
}