#include "Vaati.h"
#include "Game.h"


#define TRANS_V_COOLDOWN 12000
#define TRANS_V_DURATION 2270
#define V_HITBOX glm::ivec2(12, 26)

#define TRANS_W_COOLDOWN 4000
#define TRANS_W_DURATION 1530
#define W_HITBOX glm::ivec2(12, 12)

enum VaatiAnims
{
	MOVE_V_LEFT, MOVE_V_RIGHT, TRANS_TO_WISP, MOVE_W_LEFT, MOVE_W_RIGHT, TRANS_TO_VAATI
};


void Vaati::initMob()
{
	moveStep = 1;
	if (initAnim == MOVE_V_LEFT)
		mirror = true;

	hitboxSize = V_HITBOX;
	hitboxPos = glm::ivec2(18, 22);

	transformCooldown = TRANS_V_COOLDOWN;
	transformDuration = TRANS_V_DURATION;
	goingDown = true;
}

void Vaati::updateMob(int deltaTime)
{
	if (sprite->animation() < MOVE_W_LEFT)								// Vaati
	{
		if (sprite->animation() == TRANS_TO_WISP)
		{
			if (transformDuration >= 0)
				transformDuration -= deltaTime;
			else
			{
				transformDuration = TRANS_W_DURATION;
				hitboxSize = W_HITBOX;
				sprite->changeAnimation(initAnim);
			}
		}
		else if (transformCooldown >= 0)
		{
			transformCooldown -= deltaTime;

			if (sprite->animation() == MOVE_V_LEFT)
			{
				position.x -= moveStep;
				if (map->collisionMoveLeft(position, hitboxSize, hitboxPos) || map->fallMoveLeft(position, hitboxSize, hitboxPos))
				{
					position.x += moveStep;
					sprite->changeAnimation(MOVE_V_RIGHT);
				}
			}
			else if (sprite->animation() == MOVE_V_RIGHT)
			{
				position.x += moveStep;
				if (map->collisionMoveRight(position, hitboxSize, hitboxPos) || map->fallMoveRight(position, hitboxSize, hitboxPos))
				{
					position.x -= moveStep;
					sprite->changeAnimation(MOVE_V_LEFT);
				}
			}
		}
		else
		{
			transformCooldown = TRANS_W_COOLDOWN;
			initAnim = sprite->animation() + 3;
			sprite->changeAnimation(TRANS_TO_WISP);
			SoundCtrl::instance().putSFX("sounds/SFX/fadeIn.wav", 0.2f);
		}
	}
	else																// Wisp
	{
		if (sprite->animation() == TRANS_TO_VAATI)
		{
			if (transformDuration >= 0)
				transformDuration -= deltaTime;
			else
			{
				transformDuration = TRANS_V_DURATION;
				hitboxSize = V_HITBOX;
				sprite->changeAnimation(initAnim);
			}
		}
		else
		{
			if (transformCooldown >= 0)
				transformCooldown -= deltaTime;

			if (sprite->animation() == MOVE_W_LEFT)
			{
				position.x -= moveStep;
				if (map->collisionMoveLeft(position, hitboxSize, hitboxPos))
				{
					position.x += moveStep;
					sprite->changeAnimation(MOVE_W_RIGHT);
				}
			}
			else if (sprite->animation() == MOVE_W_RIGHT)
			{
				position.x += moveStep;
				if (map->collisionMoveRight(position, hitboxSize, hitboxPos))
				{
					position.x -= moveStep;
					sprite->changeAnimation(MOVE_W_LEFT);
				}
			}
			if (!goingDown)
			{
				position.y -= moveStep;
				if (map->collisionMoveUpEnemy(position, hitboxSize, hitboxPos - glm::ivec2(0, 7), fallStep))
				{
					goingDown = true;
					position.y += moveStep;
				}
			}
			else
			{
				position.y += moveStep;
				if (map->collisionMoveDown(position, V_HITBOX, hitboxPos, &position.y, fallStep))
				{
					if (transformCooldown <= 0)
					{
						transformCooldown = TRANS_V_COOLDOWN;
						initAnim = sprite->animation() - 3;
						sprite->changeAnimation(TRANS_TO_VAATI);
						SoundCtrl::instance().putSFX("sounds/SFX/fadeOut.wav", 0.2f);
					}
					else
						goingDown = false;
				}
			}
		}
	}
}

void Vaati::changeHorizontalDirection()
{
	int anim = sprite->animation();
	if (anim == MOVE_V_LEFT)
		sprite->changeAnimation(MOVE_V_RIGHT);
	else if (anim == MOVE_V_RIGHT)
		sprite->changeAnimation(MOVE_V_LEFT);

	else if (anim == MOVE_W_LEFT)
		sprite->changeAnimation(MOVE_W_RIGHT);
	else if (anim == MOVE_W_RIGHT)
		sprite->changeAnimation(MOVE_W_LEFT);
}

string Vaati::setSpriteSheet()
{
	return "images/Mob/Enemies/vaati.png";
}

glm::ivec2 Vaati::setSpriteSize()
{
	return glm::ivec2(48, 48);
}

glm::vec2 Vaati::setSizeInSpriteSheet()
{
	return glm::vec2(0.0625, 0.1);
}

void Vaati::setAnimations()
{
	sprite->setNumberAnimations(6);

	int i;
	sprite->setAnimationSpeed(MOVE_V_RIGHT, 9);
	for (i = 0; i < 8; ++i)
		sprite->addKeyframe(MOVE_V_RIGHT, glm::vec2((float(i) * 0.0625f), 0.0f));

	sprite->setAnimationSpeed(MOVE_V_LEFT, 9);
	for (i = 0; i < 8; ++i)
		sprite->addKeyframe(MOVE_V_LEFT, glm::vec2((float(i) * 0.0625f), 0.1f));

	sprite->setAnimationSpeed(TRANS_TO_WISP, 11);
	for (i = 0; i < 13; ++i)
		sprite->addKeyframe(TRANS_TO_WISP, glm::vec2((float(i) * 0.0625f), 0.2f));
	for (i = 0; i < 13; ++i)
		sprite->addKeyframe(TRANS_TO_WISP, glm::vec2((float(i) * 0.0625f), 0.3f));

	sprite->setAnimationSpeed(MOVE_W_LEFT, 9);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(MOVE_W_LEFT, glm::vec2((float(i) * 0.0625f), 0.4f));
	
	sprite->setAnimationSpeed(MOVE_W_RIGHT, 9);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(MOVE_W_RIGHT, glm::vec2((float(i) * 0.0625f) + 0.25f, 0.4f));

	sprite->setAnimationSpeed(TRANS_TO_VAATI, 11);
	for (i = 0; i < 9; ++i)
		sprite->addKeyframe(TRANS_TO_VAATI, glm::vec2((float(i) * 0.0625f), 0.5f));
	for (i = 0; i < 9; ++i)
		sprite->addKeyframe(TRANS_TO_VAATI, glm::vec2((float(i) * 0.0625f), 0.6f));

	sprite->changeAnimation(initAnim);
}
