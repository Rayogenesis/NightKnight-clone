#ifndef _SOUNDCTRL_INCLUDE
#define _SOUNDCTRL_INCLUDE

#include <fmod_studio.hpp>
#include <string>

class SoundCtrl
{
public:
	//SoundCtrl is a singleton.
	static SoundCtrl &instance()
	{
		static SoundCtrl SC;
		return SC;
	}
	FMOD::Studio::System* system;
	FMOD::System* lowLevelSystem;
	void putTrack(std::string track, float volume);
	void putSFX(std::string track, float volume);
	void loadSound(const std::string& file, FMOD_MODE mode);
	void playSound();
	void setVolume(float vol);
	void endMusic();
	void pauseMusic();
	void unpauseMusic();
	void update();
	SoundCtrl();
	~SoundCtrl();

	//Variables para el sonido:
	FMOD::Sound* music;
	FMOD::Channel* channel;	

	FMOD::Sound* musicSFX;
	FMOD::Channel* channelSFX;	
	void pressM() { play = !play; }

private:
	bool play = true;
};

#endif

