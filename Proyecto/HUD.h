#ifndef _HUD_INCLUDE
#define _HUD_INCLUDE


#include "Scene.h"
#include "Sprite.h"
#include "NumberGenerator.h"
#include "VidasDisplay.h"
#include "PuntuacionDisplay.h"
#include "StageDisplay.h"

class HUD
{

public:
	static HUD& instance()
	{
		static HUD instance; 
		return instance;
	};

	void init();
	void update(int vidas, int punt, int timer, int stage);
	void render();

	void setAllPositions();
	void setShield(bool s) { numVidas.setShield(s); }

private:
	VidasDisplay numVidas;
	PuntuacionDisplay puntuacion;
	PuntuacionDisplay tiempo;
	StageDisplay numStage;
};
#endif //_HUD_INCLUDE

