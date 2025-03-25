#include "Stalfos.h"
#include "Game.h"


enum StalfosAnims
{
	MOVE_LEFT, MOVE_RIGHT
};


void Stalfos::initMob()
{
	moveStep = 1;
	if (initAnim == MOVE_LEFT)
		mirror = true;

	hitboxSize = glm::ivec2(12, 22);
	hitboxPos = glm::ivec2(10, 9);
}

void Stalfos::updateMob(int deltaTime)
{
	if (sprite->animation() == MOVE_LEFT)
	{
		position.x -= moveStep;
		if (map->collisionMoveLeft(position, hitboxSize, hitboxPos) || map->fallMoveLeft(position, hitboxSize, hitboxPos))
		{
			position.x += moveStep;
			sprite->changeAnimation(MOVE_RIGHT);
		}
	}
	else
	{
		position.x += moveStep;
		if (map->collisionMoveRight(position, hitboxSize, hitboxPos) || map->fallMoveRight(position, hitboxSize, hitboxPos))
		{
			position.x -= moveStep;
			sprite->changeAnimation(MOVE_LEFT);
		}
	}
}

void Stalfos::changeHorizontalDirection()
{
	int anim = sprite->animation();
	if (anim == MOVE_LEFT)
		sprite->changeAnimation(MOVE_RIGHT);

	else sprite->changeAnimation(MOVE_LEFT);
}

string Stalfos::setSpriteSheet()
{
	return "images/Mob/Enemies/stalfos.png";
}

glm::ivec2 Stalfos::setSpriteSize()
{
	return glm::ivec2(32, 32);
}

glm::vec2 Stalfos::setSizeInSpriteSheet()
{
	return glm::vec2(0.125, 0.5);
}

void Stalfos::setAnimations()
{
	sprite->setNumberAnimations(2);

	int i;
	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	for (i = 0; i < 6; ++i)
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2((float(i) * 0.125f), 0.0f));

	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	for (i = 0; i < 6; ++i)
		sprite->addKeyframe(MOVE_LEFT, glm::vec2((float(i) * 0.125f), 0.5f));

	sprite->changeAnimation(initAnim);
}
