#include "GameManager.h"
#include "TextureManager.h"

int main() {
    TextureManager textureManager;

    textureManager.loadCharacterBodyTextures();
    textureManager.loadDarkKnightArmor();
    textureManager.loadTexture("backgroundTexture", "Assets/City/cityCenter.jpg");

    GameManager gameManager(textureManager.getTexture("backgroundTexture"));

    gameManager.run(textureManager);

    return 0;
}