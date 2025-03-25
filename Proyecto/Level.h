#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "Definitions.h"


#include "Vaati.h"
#include "Moblin.h"
#include "Stalfos.h"
#include "Key.h"
#include "Door.h"
#include "Gem.h"
#include "Shield.h"
#include "Clock.h"
#include <glm/glm.hpp>
#include <vector>


class Level
{

private:
	Level(const string& levelFile);

public:

	static Level* createLevel(const string& levelFile);

	~Level();

	int getInitPlayerPosX() const { return initPlayerTile.x; }
	int getInitPlayerPosY() const { return initPlayerTile.y; }
	int getInitPlayerAnim() const { return initPlayerAnim; }
	glm::vec2 getKeyPosition() const { return keyPosition;  }
	std::vector<Enemy*>* getEnemies() { return &enemies; }
	std::vector<Item*>* getItems() { return &items; }

private:
	bool loadLevel(const string& levelFile);

private:
	int initPlayerAnim, totalEnemies;
	glm::ivec2 initPlayerTile;
	std::vector<Enemy*> enemies;
	int* lvl;
	glm::vec2 keyPosition;
	int totalItems;
	std::vector<Item*> items;

};


#endif // _LEVEL_INCLUDE