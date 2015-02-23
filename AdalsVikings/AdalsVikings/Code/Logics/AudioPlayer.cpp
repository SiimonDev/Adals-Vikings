#include "AudioPlayer.h"
#include <iostream>

static std::map<std::string, sf::Sound*> mSounds;
static std::map<std::string, sf::Music*> mMusic;
static bool mMute = false;

// 0.0 - 1.0
static double masterSoundScale = 1.0;
static double soundEffectsScale = 0.5;
static double musicScale = 0.2;

AudioPlayer::AudioPlayer()
{
}

void AudioPlayer::playSound(Sound::ID id, std::string audioID, bool loop, float volume)
{
	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(RMI.getSoundBuffer(id));
	sound->setVolume(volume * masterSoundScale * soundEffectsScale);
	sound->setLoop(loop);
	sound->play();

	if (mSounds.find(audioID) == mSounds.end()) {
		mSounds[audioID] = sound;
	}
	else {
		delete mSounds[audioID];
		mSounds.erase(audioID);
		mSounds[audioID] = sound;
	}
}

void AudioPlayer::stopSound(std::string audioID)
{
	if (mSounds.find(audioID) != mSounds.end()) {
		mSounds[audioID]->stop();
		delete mSounds[audioID];
		mSounds.erase(audioID);
	}
}

void AudioPlayer::playMusic(std::string path, std::string musicID, bool loop, float volume)
{
	sf::Music* music = new sf::Music();
	if (!music->openFromFile(path))
		std::cout << "Failed to load music: " << path;
	music->setVolume(volume * masterSoundScale * musicScale);
	music->setLoop(loop);
	music->play();

	if (mMusic.find(musicID) == mMusic.end()) {
		mMusic[musicID] = music;
	}
	else {
		delete mMusic[musicID];
		mMusic.erase(musicID);
		mMusic[musicID] = music;
	}
}
void AudioPlayer::stopMusic(std::string musicID)
{
	if (mMusic.find(musicID) != mMusic.end()) {
		mMusic[musicID]->stop();
		delete mMusic[musicID];
		mMusic.erase(musicID);
	}
}

void AudioPlayer::update(sf::Time frameTime)
{
	std::vector<std::string> deleteID;
	for (std::map<std::string, sf::Sound*>::iterator it = mSounds.begin(); it != mSounds.end(); ++it){
		if (it->second->getStatus() == sf::Sound::Status::Stopped){
			deleteID.push_back(it->first);
		}
	}
	for each (std::string sound in deleteID){
		delete mSounds.at(sound);
		mSounds.erase(sound);
	}

	deleteID.clear();
	for (std::map<std::string, sf::Music*>::iterator it = mMusic.begin(); it != mMusic.end(); ++it){
		if (it->second->getStatus() == sf::Sound::Status::Stopped){
			deleteID.push_back(it->first);
		}
	}
	for each (std::string music in deleteID){
		delete mMusic.at(music);
		mMusic.erase(music);
	}
}

void AudioPlayer::unload()
{
	std::vector<std::string> deleteID;
	for (std::map<std::string, sf::Sound*>::iterator it = mSounds.begin(); it != mSounds.end(); ++it){
			deleteID.push_back(it->first);
	}
	for each (std::string sound in deleteID){
		delete mSounds.at(sound);
		mSounds.erase(sound);
	}

	deleteID.clear();
	for (std::map<std::string, sf::Music*>::iterator it = mMusic.begin(); it != mMusic.end(); ++it){
		deleteID.push_back(it->first);
	}
	for each (std::string music in deleteID){
		mMusic[music]->stop();
		delete mMusic.at(music);
		mMusic.erase(music);
	}
}