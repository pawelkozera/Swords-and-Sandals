#include "GameManager.h"
#include "TextureManager.h"

int main() {
    TextureManager textureManager;

    textureManager.loadCharacterBodyTextures();
    textureManager.loadDarkKnightArmor();
    textureManager.loadCityCenter();
    textureManager.loadButtons();
    textureManager.loadCursor();

    GameManager gameManager(textureManager);

    gameManager.run();

    return 0;
}