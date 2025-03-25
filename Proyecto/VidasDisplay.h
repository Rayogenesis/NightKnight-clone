#ifndef _VIDASDISPLAY_INCLUDE 
#define _VIDASDISPLAY_INCLUDE

#include "NumberGenerator.h"

class VidasDisplay
{
public:
	void init();
	void displayVidas(int num);
	void render();
	void setPosition(glm::vec2 position);
	void initTextures();
	void setShield(bool s) { bShield = s; }

private:
	Sprite* heart;
	Texture heartTex;

	Sprite* cross;
	Texture crossTex;

	Sprite* shield;
	Texture shieldTex;

	Sprite* numV;

	bool bShield;
};
#endif

