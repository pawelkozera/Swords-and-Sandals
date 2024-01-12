#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>

class SoundManager
{
private:
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
	sf::Sound sound;
public:
	void setUp();
	void setVolume(float volume);
	void playAttackHit();
	void playAttackMissInReach();
};

