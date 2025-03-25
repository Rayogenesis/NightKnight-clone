#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Mob.h"

#include "Game.h"


void Mob::init(TileMap* tileMap, const glm::ivec2& tileMapPos, const glm::ivec2& iniPos, int iniAnim, ShaderProgram& shaderProgram)
{
	fallStep = 5;
	initAnim = iniAnim;
	mirror = false;
	bPaint = true;

	spritesheet.loadFromFile(setSpriteSheet(), TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(setSpriteSize(), setSizeInSpriteSheet(), &spritesheet, &shaderProgram);
	setAnimations();

	tileMapDispl = tileMapPos;
	map = tileMap;
	initMob();
	initPos = glm::ivec2(iniPos.x - hitboxPos.x, iniPos.y - hitboxPos.y - hitboxSize.y);
	position = initPos;
	if (mirror) position.x += TILESIZE.x - hitboxSize.x;
	setPosition(position);
}

void Mob::update(int deltaTime)
{
	updateMob(deltaTime);
	setPosition(position);
	sprite->update(deltaTime);
}

void Mob::render()
{
	if (bPaint) sprite->render();
}

void Mob::setPosition(const glm::ivec2& pos)
{
	position = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

