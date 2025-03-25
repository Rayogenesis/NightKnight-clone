#include "Moblin.h"
#include "SoundCtrl.h"


#define ANGER_COOLDOWN 1000

#define BODY_HITBOX_SIZE glm::ivec2(28, 26)
#define BODY_HITBOX_POS glm::ivec2(11, 2)

#define SPEAR_HITBOX_SIZE glm::ivec2(50, 16)
#define SPEAR_HITBOX_POS glm::ivec2(0, 6)

enum MoblinAnims
{
	STAND_LEFT, STAND_RIGHT, READY_LEFT, READY_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Moblin::initMob()
{
	moveStep = 6;
	if (initAnim == STAND_LEFT)
		mirror = true;

	hitboxSize = BODY_HITBOX_SIZE;
	hitboxPos = BODY_HITBOX_POS;

	angerCooldown = ANGER_COOLDOWN;
	angry = false;
}

void Moblin::updateMob(int deltaTime)
{
	if (sprite->animation() == MOVE_LEFT)
	{
		position.x -= moveStep;
		if (map->collisionMoveLeftEnemy(position, hitboxSize, hitboxPos, &position.x, moveStep) ||
			map->fallMoveLeft(position, hitboxSize, hitboxPos, &position.x, moveStep))
		{
			angry = false;
			sprite->changeAnimation(STAND_RIGHT);
		}
			
	}
	else if (sprite->animation() == MOVE_RIGHT)
	{
		position.x += moveStep;
		if (map->collisionMoveRightEnemy(position, hitboxSize, hitboxPos, &position.x, moveStep) ||
			map->fallMoveRight(position, hitboxSize, hitboxPos, &position.x, moveStep))
		{
			angry = false;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (playerInSight())
	{
		if (angry)
		{
			angerCooldown -= deltaTime;
			if (angerCooldown <= 0)
			{
				SoundCtrl::instance().putSFX("sounds/SFX/scream.wav", 0.2f);
				angerCooldown = ANGER_COOLDOWN;

				if (sprite->animation() == READY_LEFT)
					sprite->changeAnimation(MOVE_LEFT);

				else if (sprite->animation() == READY_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
			}
		}
		else
		{
			angry = true;	
			SoundCtrl::instance().putSFX("sounds/SFX/spear.wav", 0.2f);
			if (sprite->animation() == STAND_LEFT)
				sprite->changeAnimation(READY_LEFT);

			else if (sprite->animation() == STAND_RIGHT)
				sprite->changeAnimation(READY_RIGHT);
		}
	}
	else if (angry)
	{
		angry = false;
		if (sprite->animation() == READY_LEFT)
			sprite->changeAnimation(STAND_LEFT);

		else if (sprite->animation() == READY_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	else
	{
		angerCooldown += deltaTime;
		if (angerCooldown > ANGER_COOLDOWN)
			angerCooldown = ANGER_COOLDOWN;
	}
}

bool Moblin::collision()
{
	glm::ivec2 topLeft = getTopLeft();
	glm::ivec2 botRight = getBotRight();

	if (!(playerBotRight.x < topLeft.x || botRight.x < playerTopLeft.x) &&
		!(playerBotRight.y < topLeft.y || botRight.y < playerTopLeft.y))
	{
		return true;
	}

	if (sprite->animation() > STAND_RIGHT)
	{
		topLeft = position + SPEAR_HITBOX_POS;
		botRight = position + SPEAR_HITBOX_POS + SPEAR_HITBOX_SIZE;

		if (!(playerBotRight.x < topLeft.x || botRight.x < playerTopLeft.x) &&
			!(playerBotRight.y < topLeft.y || botRight.y < playerTopLeft.y))
		{
			return true;
		}
	}
	return false;
}

bool Moblin::playerInSight()
{
	glm::ivec2 topLeft = getTopLeft();
	glm::ivec2 botRight = getBotRight();

	if (topLeft.y <= playerBotRight.y && playerBotRight.y <= botRight.y)
	{
		if (sprite->animation() % 2 == 0 && playerBotRight.x <= topLeft.x)
			return true;

		if (sprite->animation() % 2 == 1 && botRight.x <= playerTopLeft.x)
			return true;
	}
	return false;
}

string Moblin::setSpriteSheet()
{
	return "images/Mob/Enemies/moblin.png";
}

glm::ivec2 Moblin::setSpriteSize()
{
	return glm::ivec2(50, 32);
}

glm::vec2 Moblin::setSizeInSpriteSheet()
{
	return glm::vec2(0.25, 0.25);
}

void Moblin::setAnimations()
{
	sprite->setNumberAnimations(6);

	int i;
	sprite->setAnimationSpeed(STAND_RIGHT, 3);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(STAND_RIGHT, glm::vec2((float(i) * 0.25f), 0.0f));

	sprite->setAnimationSpeed(STAND_LEFT, 3);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(STAND_LEFT, glm::vec2((float(i) * 0.25f), 0.25f));

	sprite->setAnimationSpeed(READY_RIGHT, 4);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(READY_RIGHT, glm::vec2(0.f, 0.50f));

	sprite->setAnimationSpeed(READY_LEFT, 4);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(READY_LEFT, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2((float(i) * 0.25f), 0.50f));

	sprite->setAnimationSpeed(MOVE_LEFT, 10);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(MOVE_LEFT, glm::vec2((float(i) * 0.25f), 0.75f));

	sprite->changeAnimation(initAnim);
}
