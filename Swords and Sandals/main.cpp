#include "GameManager.h"
#include "TextureManager.h"

int main() {
    GameManager gameManager;
    TextureManager textureManager;

    textureManager.loadCharacterBodyTextures();
    textureManager.loadDarkKnightArmor();

    gameManager.run(textureManager);

    return 0;
}