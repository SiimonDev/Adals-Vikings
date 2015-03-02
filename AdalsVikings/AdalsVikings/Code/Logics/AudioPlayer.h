#pragma once
#include "ResourceManager.h"

class AudioPlayer
{
public:
	static void playSound(Sound::ID id, std::string audioID, bool loop, float volume = 50);
	static void playRandomSound(Footsteps::ID id, float volume = 50);
	static void stopSound(std::string audioID);

	static void playHDDSound(HDDSound::ID id, bool loop, float volume = 50);
	static void stopHDDSound(HDDSound::ID id);

	static void update(sf::Time frameTime);
	static void unload();
private:
	AudioPlayer();
	AudioPlayer(const AudioPlayer&);
	void operator=(const AudioPlayer&);
};