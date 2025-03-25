#ifndef _STALFOS_INCLUDE
#define _STALFOS_INCLUDE


#include "Enemy.h"


class Stalfos : public Enemy
{

protected:
	void initMob();
	void updateMob(int deltaTime);

	void changeHorizontalDirection();
	string setSpriteSheet();
	glm::ivec2 setSpriteSize();
	glm::vec2 setSizeInSpriteSheet();
	void setAnimations();

};


#endif // _STALFOS_INCLUDE
