#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Level.h"



using namespace std;


Level* Level::createLevel(const string& levelFile)
{
	Level* lvl = new Level(levelFile);

	return lvl;
}


Level::Level(const string& levelFile)
{
	loadLevel(levelFile);
}

Level::~Level()
{
	for (Enemy* enemy : enemies)
		if (enemy != NULL)
			delete enemy;
	enemies.clear();

	for (Item* item : items)
		if (item != NULL)
			delete item;
	items.clear();
	
	if (lvl != NULL)
		delete lvl;
}

bool Level::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line;
	stringstream sstream;
	int i, initAnim;
	char enemyType;
	glm::ivec2 initTile; 

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);																// LEVEL
	if (line.compare(0, 5, "LEVEL") != 0)
		return false;
	getline(fin, line);																// Initial player tile & anim
	sstream.str(line);
	sstream >> initPlayerTile.x >> initPlayerTile.y >> initPlayerAnim;
	getline(fin, line);																// Number of enemies
	sstream.str(line);
	sstream >> totalEnemies;
	for (i = 0; i < totalEnemies; ++i)
	{
		Enemy* enemy;
		getline(fin, line);															// Enemy type, initial enemy tile & anim
		sstream.str(line);
		sstream >> enemyType >> initTile.x >> initTile.y >> initAnim;
		
		if (enemyType == 'V')
			enemy = new Vaati();

		else if (enemyType == 'M')
			enemy = new Moblin();

		else enemy = new Stalfos();

		enemy->setType(enemyType);
		enemy->setInitTile(initTile);
		enemy->setInitAnim(initAnim);

		enemies.push_back(enemy);
	}

	//Read items:
	char itemType;
	int timeToAppear;
	glm::ivec2 initialTile;
	getline(fin, line);
	sstream.str(line);
	sstream >> totalItems;

	for (int i = 0; i < totalItems; ++i)
	{
		Item* item;
		getline(fin, line);
		sstream.str(line);
		sstream >> itemType >> initialTile.x >> initialTile.y >> timeToAppear;

		if (itemType == 'K') item = new Key();
		else if (itemType == 'D') item = new Door();
		else if (itemType == 'G') item = new Gem();
		else if (itemType == 'S') item = new Shield();
		else item = new Clock();

		item->setInitialTile(initialTile);
		item->setType(itemType);
		item->setTimeToAppear(timeToAppear);

		items.push_back(item);
	}
	
	fin.close();

	return true;
}