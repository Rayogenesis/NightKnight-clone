#include "SoundCtrl.h"
#include <stdio.h>
#include <fmod_errors.h>


//void SoundCtrl::putSFX(std::string track, float volume)
//{
//	loadSound(track, FMOD_LOOP_OFF | FMOD_CREATESTREAM);
//	playSound();
//	setVolume(volume);
//}

void SoundCtrl::putSFX(std::string track, float volume)
{
	lowLevelSystem->createSound(track.c_str(), FMOD_LOOP_OFF | FMOD_CREATESTREAM, nullptr, &musicSFX);
	lowLevelSystem->playSound(musicSFX, nullptr, false, &channelSFX);
	channelSFX->setVolume(volume);
}

void SoundCtrl::putTrack(std::string track, float volume)
{
	if (play)
	{
		loadSound(track, FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);
		playSound();
		setVolume(volume);
	}
}

void SoundCtrl::pauseMusic()
{
	channel->setPaused(true);
}

void SoundCtrl::unpauseMusic()
{
	channel->setPaused(false);
}

void SoundCtrl::loadSound(const std::string& file, FMOD_MODE mode) {
	lowLevelSystem->createSound(file.c_str(), mode, nullptr, &music);
}

void SoundCtrl::playSound() {
	lowLevelSystem->playSound(music, nullptr, false, &channel);
}

void SoundCtrl::setVolume(float vol)
{
	channel->setVolume(vol);
}

void SoundCtrl::endMusic()
{
	channel->stop();
}

void SoundCtrl::update() {
	system->update();
	lowLevelSystem->update();
}

SoundCtrl::SoundCtrl() : system(NULL) {
	FMOD_RESULT result;
	result = FMOD::Studio::System::create(&system); // Create the Studio System object.
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}

	// Initialize FMOD Studio, which will also initialize FMOD Low Level
	result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
	system->getLowLevelSystem(&lowLevelSystem);
}


SoundCtrl::~SoundCtrl() {
	system->unloadAll();
	system->release();
}

