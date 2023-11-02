#include "GameManager.h"
#include "TextureManager.h"

int main() {
    TextureManager textureManager;

    textureManager.loadCharacterBodyTextures();
    textureManager.loadDarkKnightArmor();
    textureManager.loadCityCenter();
    textureManager.loadButtons();

    GameManager gameManager;

    gameManager.run(textureManager);

    return 0;
}