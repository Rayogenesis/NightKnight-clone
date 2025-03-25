#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Mob.h"


class Enemy : public Mob
{
public:
	void setType(char t) { type = t; }
	void setInitTile(glm::ivec2 iniTile) { initTile = iniTile; }

	void setPlayerTopLeft(glm::ivec2 playerTL) { playerTopLeft = playerTL; }
	void setPlayerBotRight(glm::ivec2 playerBR) { playerBotRight = playerBR; }

	bool collision();

	char getType() { return type; }
	int getInitTileX() { return initTile.x; }
	int getInitTileY() { return initTile.y; }

protected:
	virtual void changeHorizontalDirection() { ; }

protected:
	char type;
	glm::ivec2 initTile, playerTopLeft, playerBotRight;

};


#endif // _ENEMY_INCLUDE
