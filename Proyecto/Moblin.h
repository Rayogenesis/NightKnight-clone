#ifndef _MOBLIN_INCLUDE
#define _MOBLIN_INCLUDE


#include "Enemy.h"


class Moblin : public Enemy
{
public:
	bool collision();

protected:
	void initMob();
	void updateMob(int deltaTime);

	string setSpriteSheet();
	glm::ivec2 setSpriteSize();
	glm::vec2 setSizeInSpriteSheet();
	void setAnimations();

	bool playerInSight();

private:
	int angerCooldown;
	bool angry;

};


#endif // _MOBLIN_INCLUDE
