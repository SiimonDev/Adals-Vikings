#pragma once
#include "ResourceManager.h"

#define AudioPlayerI AudioPlayer::getInstance()

class AudioPlayer
{
public:
	static AudioPlayer &getInstance();

	void playSound(Sound::ID id, std::string audioID, bool loop, float volume = 50);
	void stopSound(std::string audioID);

	void playMusic(std::string path, std::string musicID, bool loop, float volume = 50);
	void stopMusic(std::string musicID);

	void update(sf::Time frameTime);
	void unload();
private:
	AudioPlayer();
	AudioPlayer(const AudioPlayer&);
	void operator=(const AudioPlayer&);

	std::map<std::string, sf::Sound*> mSounds;
	std::map<std::string, sf::Music*> mMusic;
	bool mMute = false;

	// 0.0 - 1.0
	double masterSoundScale;
	double soundEffectsScale;
	double musicScale;
};