#include "StageDisplay.h"

void StageDisplay::init()
{
	initTextures();
	num.init(2);
	stage = Sprite::createSprite(glm::ivec2(90, 20), glm::vec2(1.f, 1.f), &stageTex, &TEX_PROGRAM);
}

void StageDisplay::initTextures()
{
	stageTex.loadFromFile("images/HUD/Stage/stage.png", TEXTURE_PIXEL_FORMAT_RGBA);
	stageTex.setMinFilter(GL_NEAREST);
	stageTex.setMagFilter(GL_NEAREST);
}

void StageDisplay::render()
{
	stage->render();
	num.render();
}

void StageDisplay::displayLevel(int number)
{
	num.displayNum(number);
}

void StageDisplay::setPosition(glm::vec2 pos)
{
	stage->setPosition(pos);
	num.setPosition(pos + glm::vec2(110, -2.5f));
}

