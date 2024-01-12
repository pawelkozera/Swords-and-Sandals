#include "SoundManager.h"


void SoundManager::setUp() {
    soundBuffers["attackHit"] = sf::SoundBuffer();
    soundBuffers["attackHit"].loadFromFile("Sounds/attackHit.wav");

    soundBuffers["attackMissInReach"] = sf::SoundBuffer();
    soundBuffers["attackMissInReach"].loadFromFile("Sounds/attackMissInReach.wav");
}

void SoundManager::setVolume(float volume) {
    sound.setVolume(volume);
}

void SoundManager::playAttackHit() {
    sound.setBuffer(soundBuffers["attackHit"]);
    sound.play();
}

void SoundManager::playAttackMissInReach() {
    sound.setBuffer(soundBuffers["attackMissInReach"]);
    sound.play();
}