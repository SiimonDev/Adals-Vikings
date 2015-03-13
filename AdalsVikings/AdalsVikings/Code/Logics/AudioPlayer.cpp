#include "AudioPlayer.h"
#include <iostream>

static std::vector<sf::Sound*> mNonLoopSounds;

static std::map<std::string, sf::Sound*> mSounds;
static std::map<HDDSound::ID, sf::Music*> mHDDSound;
static bool mMute = false;

// 0.0 - 1.0
static double masterSoundScale = 1.0f;
static double soundEffectsScale = 0.7f;
static double musicScale = 0.5f;

AudioPlayer::AudioPlayer()
{
}

void AudioPlayer::playSound(Sound::ID id, std::string audioID, bool loop, float volume)
{
	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(RMI.getResource(id));
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

void AudioPlayer::playRandomSound(Footsteps::ID id, float volume)
{
	int index = rand() % RMI.getResource(id).size();

	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*RMI.getResource(id).at(index));
	sound->setVolume(volume * masterSoundScale * soundEffectsScale);
	sound->setLoop(false);
	sound->play();
	mNonLoopSounds.push_back(sound);
}

void AudioPlayer::stopSound(std::string audioID)
{
	if (mSounds.find(audioID) != mSounds.end()) {
		mSounds[audioID]->stop();
		delete mSounds[audioID];
		mSounds.erase(audioID);
	}
}

void AudioPlayer::playHDDSound(HDDSound::ID id, bool loop, float volume)
{
	if (mHDDSound.find(id) == mHDDSound.end()) {
		sf::Music* music = new sf::Music();
		if (!music->openFromFile(RMI.getFilePath(id)))
			std::cout << "Failed to load music: " << RMI.getFilePath(id);
		music->setVolume(volume * masterSoundScale * musicScale);
		music->setLoop(loop);
		music->play();

		mHDDSound[id] = music;
	}
	else {
		mHDDSound[id]->setVolume(volume * masterSoundScale * musicScale);
		mHDDSound[id]->setLoop(loop);
	}
}
void AudioPlayer::stopHDDSound(HDDSound::ID id)
{
	if (mHDDSound.find(id) != mHDDSound.end()) {
		mHDDSound[id]->stop();
		delete mHDDSound[id];
		mHDDSound.erase(id);
	}
}

void AudioPlayer::update(sf::Time frameTime)
{
	// Delete all NonLoop sound that has been stopped
	for (size_t i = 0; i < mNonLoopSounds.size(); i++)
	{
		if (mNonLoopSounds[i]->getStatus() == sf::Sound::Status::Stopped){
			delete mNonLoopSounds[i];
			mNonLoopSounds.erase(mNonLoopSounds.begin() + i);
			i--;
		}
	}

	// Delete all sounds that has been stopped
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

	// Delete all music that has been stopped
	std::vector<HDDSound::ID> deleteHDDSoundID;
	for (std::map<HDDSound::ID, sf::Music*>::iterator it = mHDDSound.begin(); it != mHDDSound.end(); ++it){
		if (it->second->getStatus() == sf::Sound::Status::Stopped){
			deleteHDDSoundID.push_back(it->first);
		}
	}
	for each (HDDSound::ID id in deleteHDDSoundID){
		delete mHDDSound.at(id);
		mHDDSound.erase(id);
	}
}

void AudioPlayer::unload()
{
	// Delete all NonLoop sounds
	for each (sf::Sound* sound in mNonLoopSounds){
		delete sound;
	}
	mNonLoopSounds.clear();

	// Delete all sounds
	std::vector<std::string> deleteID;
	for (std::map<std::string, sf::Sound*>::iterator it = mSounds.begin(); it != mSounds.end(); ++it){
			deleteID.push_back(it->first);
	}
	for each (std::string sound in deleteID){
		delete mSounds.at(sound);
		mSounds.erase(sound);
	}

	// Delete all the Music
	for (std::map<HDDSound::ID, sf::Music*>::iterator it = mHDDSound.begin(); it != mHDDSound.end(); ++it){
		delete it->second;
	}
	mHDDSound.clear();
}
