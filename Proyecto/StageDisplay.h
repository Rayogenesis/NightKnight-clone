#ifndef _STAGEDISPLAY_INCLUDE
#define _STAGEDISPLAY_INCLUDE

#include "NumberGenerator.h"
#include "PuntuacionDisplay.h"

class StageDisplay 
{
public:
	void init();
	void initTextures();
	void render();
	void displayLevel(int num);
	void setPosition(glm::vec2 position);

private:
	PuntuacionDisplay num;

	Texture stageTex;
	Sprite* stage;
};

#endif //_STAGEDISPLAY_INCLUDE

