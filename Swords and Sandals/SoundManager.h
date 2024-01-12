#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>

class SoundManager
{
private:
	static std::unordered_map<std::string, sf::SoundBuffer>& getSoundBuffers();
	static sf::Sound& getSound();
public:
	static void setUp();
	static void setVolume(float volume);
	static float getVolume();
	static void playAttackHit();
	static void playAttackMissInReach();
	static void playAttackMissNotInReach();
	static void playWalk();
	static void playRest();
	static void playUIButton();
};

