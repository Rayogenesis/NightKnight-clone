#include "HUD.h"


void HUD::init()
{
	NumberGenerator::instance().initTexture();
	numVidas.init();
	puntuacion.init(6);
	tiempo.init(2);
	numStage.init();
	setAllPositions();
}

void HUD::update(int vidas, int punt, int timer, int stage)
{
	numVidas.displayVidas(vidas);
	puntuacion.displayNum(punt);
	tiempo.displayNum(timer);
	numStage.displayLevel(stage);
}

void HUD::render()
{	
	numVidas.render();
	puntuacion.render();
	tiempo.render();
	numStage.render();
}

void HUD::setAllPositions()
{
	numVidas.setPosition(glm::vec2(20, 25));
	puntuacion.setPosition(glm::vec2(120, 25));
	tiempo.setPosition(glm::vec2(300, 25));
	numStage.setPosition(glm::vec2(450, 25));
}


