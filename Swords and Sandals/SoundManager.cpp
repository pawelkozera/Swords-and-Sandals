#include "SoundManager.h"

std::unordered_map<std::string, sf::SoundBuffer>& SoundManager::getSoundBuffers() {
    static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    return soundBuffers;
}

sf::Sound& SoundManager::getSound() {
    static sf::Sound sound;
    return sound;
}

void SoundManager::setUp() {
    auto& soundBuffers = getSoundBuffers();

    soundBuffers["attackHit"] = sf::SoundBuffer();
    soundBuffers["attackHit"].loadFromFile("Sounds/attackHit.wav");

    soundBuffers["attackMissInReach"] = sf::SoundBuffer();
    soundBuffers["attackMissInReach"].loadFromFile("Sounds/attackMissInReach.wav");

    soundBuffers["attackMissNotInReach"] = sf::SoundBuffer();
    soundBuffers["attackMissNotInReach"].loadFromFile("Sounds/attackMissNotInReach.wav");

    soundBuffers["walk"] = sf::SoundBuffer();
    soundBuffers["walk"].loadFromFile("Sounds/walk.wav");

    soundBuffers["rest"] = sf::SoundBuffer();
    soundBuffers["rest"].loadFromFile("Sounds/rest.wav");

    soundBuffers["uiButton"] = sf::SoundBuffer();
    soundBuffers["uiButton"].loadFromFile("Sounds/uiButton.wav");
}

void SoundManager::setVolume(float volume) {
    getSound().setVolume(volume);
}

float SoundManager::getVolume() {
    return getSound().getVolume();
}

void SoundManager::playAttackHit() {
    getSound().setBuffer(getSoundBuffers()["attackHit"]);
    getSound().play();
}

void SoundManager::playAttackMissInReach() {
    getSound().setBuffer(getSoundBuffers()["attackMissInReach"]);
    getSound().play();
}

void SoundManager::playAttackMissNotInReach() {
    getSound().setBuffer(getSoundBuffers()["attackMissNotInReach"]);
    getSound().play();
}

void SoundManager::playWalk() {
    getSound().setBuffer(getSoundBuffers()["walk"]);
    getSound().play();
}

void SoundManager::playRest() {
    getSound().setBuffer(getSoundBuffers()["rest"]);
    getSound().play();
}

void SoundManager::playUIButton() {
    getSound().setBuffer(getSoundBuffers()["uiButton"]);
    getSound().play();
}