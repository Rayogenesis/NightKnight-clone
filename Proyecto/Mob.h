#ifndef _MOB_INCLUDE
#define _MOB_INCLUDE

#include "Definitions.h"


#include "Sprite.h"
#include "TileMap.h"


class Mob
{

public:
	void init(TileMap* tileMap, const glm::ivec2& tileMapPos, const glm::ivec2& iniPos, int iniAnim, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setInitAnim(int iniAnim) { initAnim = iniAnim; }
	void unpaint() { bPaint = false; }

	int getInitAnim() { return initAnim; }
	bool bePainted() { return bPaint; }
	glm::ivec2 getTopLeft() { return (position + hitboxPos); }
	glm::ivec2 getBotRight() { return (position + hitboxPos + hitboxSize); }

protected:
	virtual void initMob() = 0;
	virtual void updateMob(int deltaTime) = 0;

	void setPosition(const glm::ivec2& pos);
	virtual string setSpriteSheet() = 0;
	virtual glm::ivec2 setSpriteSize() = 0;
	virtual glm::vec2 setSizeInSpriteSheet() = 0;
	virtual void setAnimations() = 0;

protected:
	int startY, jumpHeight, jumpAngle, jumpAngleStep, fallStep, moveStep, coyoteTime, initAnim;
	bool mirror, bPaint;
	glm::ivec2 tileMapDispl, initPos, position, hitboxSize, hitboxPos;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};


#endif // _MOB_INCLUDE