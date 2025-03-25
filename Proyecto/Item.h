#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE

#include "Texture.h"
#include "Sprite.h"

class Item
{
public:
	void init();
	void update(int deltaTime);
	void render();

	void changeBPaint(bool b) { bPaint = b; }
	void setType(char type) { this->type = type; }
	void setTimeToAppear(int time) { this->timeToAppear = time*1000; }
	void setInitialTile(glm::vec2 tile) { this->initTile = tile; }
	void setPlayerTopLeft(glm::ivec2 playerTL) { playerTopLeft = playerTL; }
	void setPlayerBotRight(glm::ivec2 playerBR) { playerBotRight = playerBR; }
	
	virtual bool collision();
	bool getBPaint() { return bPaint; }
	bool isTaken() { return taken; }
	char getType() const { return this->type; }
	int getTimeToAppear() const { return timeToAppear; }
	glm::ivec2 getTopLeft() { return (position); }
	glm::ivec2 getBotRight() { return (position + hitboxSize); }
	
protected:
	virtual void initItem() { ; }
	virtual void updateItem(int deltaTime) { ; }

	void initTextures();
	void setPosition();
	
	virtual string getImagePath() = 0;
	virtual void initSprites() = 0;

protected:
	Texture itemTex;
	Sprite* itemSprite;
	bool bPaint, taken;
	glm::ivec2 initTile, position, hitboxSize, playerTopLeft, playerBotRight;
	char type;
	int timeToAppear, timeToDisappear;
};

#endif
