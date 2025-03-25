#include <GL/glew.h>
#include <GL/glut.h>

#include "Player.h"

#include "Game.h"


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, HURT_LEFT, HURT_RIGHT, FALL_LEFT, FALL_RIGHT
};

void Player::initMob()
{
	jumpHeight = 52;
	jumpAngleStep = 6;
	moveStep = 2;
	coyoteTime = 4;
	bFalling = false;
	bJumping = false;
	
	health = 3;
	hurtTime = 0;
	blink = 5;
	hurt = false;
	reset = true;
	godMode = false;
	shield = false;

	puntuacion = 0;
	puntGoal = 1000;
	key = false;
	clock = false;
	clockTime = 5000;
	win = false;

	hitboxSize = glm::ivec2(16, 32);
	hitboxPos = glm::ivec2(17, 26);
}

void Player::updateMob(int deltaTime)
{
	if (hurt) updateHurt(deltaTime);
	if (hurtTime <= 1000) updateMovement();
	updateStats(deltaTime);
}

void Player::updateHurt(int deltaTime)
{
	hurtTime -= deltaTime;
	if (hurtTime <= 0)
	{
		hurtTime = 0;
		blink = 5;
		hurt = false;
		reset = true;
		bPaint = true;
	}
	else if (hurtTime <= 1000)
	{
		if (reset)
		{
			setPosition(initPos);
			sprite->changeAnimation(initAnim);
			setPosition(initPos);
			reset = false;
		}
		if (--blink == 0)
		{
			blink = 5;
			if (!win) bPaint = !bPaint;
		}
	}
	else if (sprite->animation() == FALL_LEFT)
	{
		position.y += fallStep;
		if (map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep))
			sprite->changeAnimation(HURT_LEFT);
	}
	else if (sprite->animation() == FALL_RIGHT)
	{
		position.y += fallStep;
		if (map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep))
			sprite->changeAnimation(HURT_RIGHT);
	}
}

void Player::updateMovement()
{
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (!Game::instance().getSpecialKey(GLUT_KEY_RIGHT) || bFalling || bJumping)
		{
			position.x -= moveStep;
			bool c = map->collisionMoveLeft(position, hitboxSize, hitboxPos);
			if (c) position.x += moveStep;

			if (bFalling)
			{
				map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);

				if (sprite->animation() != JUMP_LEFT)
					sprite->changeAnimation(JUMP_LEFT);
			}
			else if (bJumping)
			{
				if (sprite->animation() != JUMP_LEFT)
					sprite->changeAnimation(JUMP_LEFT);
			}
			else
			{
				map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);

				if (c && sprite->animation() != STAND_LEFT)
					sprite->changeAnimation(STAND_LEFT);
				else if (!c && sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
			}
		}
		else
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT) || bFalling || bJumping)
		{
			position.x += moveStep;
			bool c = map->collisionMoveRight(position, hitboxSize, hitboxPos);
			if (c) position.x -= moveStep;

			if (bFalling)
			{
				map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);

				if (sprite->animation() != JUMP_RIGHT)
					sprite->changeAnimation(JUMP_RIGHT);
			}
			else if (bJumping)
			{
				if (sprite->animation() != JUMP_RIGHT)
					sprite->changeAnimation(JUMP_RIGHT);
			}
			else
			{
				map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);

				if (c && sprite->animation() != STAND_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
				else if (!c && sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
			}
		}
		else
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	if (bJumping)
	{
		int newPos;
		coyote = 0;
		jumpAngle += jumpAngleStep;

		if (jumpAngle == 180)
		{
			bJumping = false;
		}
		else if (jumpAngle < 78)
		{
			newPos = int(startY - jumpHeight * sin(3.14159f * jumpAngle / 156.f));
			position.y = newPos;

			if (jumpAngle == 12)
			{
				if (sprite->animation() % 2 == 0 && sprite->animation() != JUMP_LEFT)
					sprite->changeAnimation(JUMP_LEFT);
				else if (sprite->animation() % 2 == 1 && sprite->animation() != JUMP_RIGHT)
					sprite->changeAnimation(JUMP_RIGHT);
			}
			if (map->collisionMoveUp(position, hitboxSize, hitboxPos, &position.y, fallStep))
			{
				startY = position.y + jumpHeight;
				jumpAngle = 78;
			}
		}
		else if (jumpAngle == 78)
		{
			newPos = int(startY - jumpHeight);
			position.y = newPos;
		}
		else if (jumpAngle < 102)
		{
			bJumping = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
			if (!bJumping)
			{
				if (sprite->animation() % 2 == 0)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() % 2 == 1)
					sprite->changeAnimation(STAND_RIGHT);
			}
		}

		else if (jumpAngle == 102)
		{
			bJumping = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
			bFalling = bJumping;
			if (!bJumping)
			{
				if (sprite->animation() % 2 == 0)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() % 2 == 1)
					sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else
		{
			newPos = int(startY - jumpHeight * sin(3.14159f * (jumpAngle - 24) / 156.f));
			newPos <= position.y + fallStep ? position.y = newPos : position.y += fallStep;
			bJumping = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
			if (!bJumping)
			{
				if (sprite->animation() % 2 == 0)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() % 2 == 1)
					sprite->changeAnimation(STAND_RIGHT);
			}
		}
	}
	else
	{
		position.y += fallStep;
		bFalling = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
		if (!bFalling)
		{
			if (!hurt && !godMode && map->collisionSpikesDown(position, hitboxSize, hitboxPos, &position.y, fallStep)) hit();
			else
			{
				map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);
				coyote = coyoteTime;

				if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !map->collisionMoveUp(glm::ivec2(position.x, position.y - 1), hitboxSize, hitboxPos, &position.y, fallStep))
				{
					SoundCtrl::instance().putSFX("sounds/SFX/jump.wav", 0.2f);
					bJumping = true;
					jumpAngle = 0;
					startY = position.y;
				}
				else if (sprite->animation() == JUMP_LEFT)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() == JUMP_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else
		{
			if (coyote) {
				position.y -= fallStep + coyote - coyoteTime;
				coyote -= 1;
				if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !map->collisionMoveUp(glm::ivec2(position.x, position.y - 1), hitboxSize, hitboxPos, &position.y, fallStep))
				{
					SoundCtrl::instance().putSFX("sounds/SFX/jump.wav", 0.2f);
					bJumping = true;
					jumpAngle = 0;
					startY = position.y;
				}
			}
			if (sprite->animation() % 2 == 0 && sprite->animation() != JUMP_LEFT)
				sprite->changeAnimation(JUMP_LEFT);
			else if (sprite->animation() % 2 == 1 && sprite->animation() != JUMP_RIGHT)
				sprite->changeAnimation(JUMP_RIGHT);
		}
	}
}

void Player::updateStats(int deltaTime)
{
	while (puntGoal <= puntuacion)
	{
		SoundCtrl::instance().putSFX("sounds/SFX/obtenerVida.wav", 0.2f);
		++health;
		puntGoal += 1000;
	}
	if (clock)
	{
		clockTime -= deltaTime;
		if (clockTime <= 0)
		{
			clock = false;
			clockTime = 5000;
		}
	}
		
}

void Player::hit()
{
	if (!godMode)
	{	
		if (shield)
		{
			SoundCtrl::instance().putSFX("sounds/SFX/shieldbreaking.wav", 0.2f);
			shield = false;
			hurtTime = 1000;
			hurt = true;
			reset = false;
		}
		else {
			SoundCtrl::instance().putSFX("sounds/SFX/hurt.wav", 0.2f);
			--health;
			hurtTime = 4000;
			hurt = true;
			reset = true;
			bJumping = false;
			bFalling = false;

			if (sprite->animation() % 2 == 0)
			{
				if (sprite->animation() == JUMP_LEFT)
					sprite->changeAnimation(FALL_LEFT);
				else sprite->changeAnimation(HURT_LEFT);
			}
			else
			{
				if (sprite->animation() == JUMP_RIGHT)
					sprite->changeAnimation(FALL_RIGHT);
				else sprite->changeAnimation(HURT_RIGHT);
			}
		}
	}
}

void Player::takeItem(char item)
{
	if (item == 'K')
	{
		SoundCtrl::instance().putSFX("sounds/SFX/pickup.wav", 0.2f);
		key = true;
	}
	else if (item == 'G')
	{
		SoundCtrl::instance().putSFX("sounds/SFX/pickup.wav", 0.2f);
		puntuacion += 500;
	}
	else if (item == 'S')
	{
		SoundCtrl::instance().putSFX("sounds/SFX/pickup.wav", 0.2f);
		shield = true;
	}
	else if (item == 'C')
	{
		SoundCtrl::instance().putSFX("sounds/SFX/clockiti.mp3", 10.0f);
		clock = true;
	}
	else if (item == 'D')
	{
		win = true;
	}
}

string Player::setSpriteSheet()
{
	return "images/Mob/Player/zero.png";
}

glm::ivec2 Player::setSpriteSize()
{
	return glm::ivec2(64, 64);
}

glm::vec2 Player::setSizeInSpriteSheet()
{
	return glm::vec2(0.0625, 0.1);
}

void Player::setAnimations()
{
	sprite->setNumberAnimations(12);

	int i;
	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	for (i = 0; i < 11; ++i)
		sprite->addKeyframe(STAND_RIGHT, glm::vec2((float(i) * 0.0625f), 0.0f));

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	for (i = 0; i < 11; ++i)
		sprite->addKeyframe(STAND_LEFT, glm::vec2((float(i) * 0.0625f), 0.1f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	for (i = 0; i < 8; ++i)
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2((float(i) * 0.0625f), 0.2f));

	sprite->setAnimationSpeed(MOVE_LEFT, 10);
	for (i = 0; i < 8; ++i)
		sprite->addKeyframe(MOVE_LEFT, glm::vec2((float(i) * 0.0625f), 0.3f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 10);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2((float(i) * 0.0625f), 0.4f));

	sprite->setAnimationSpeed(JUMP_LEFT, 10);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(JUMP_LEFT, glm::vec2((float(i) * 0.0625f), 0.5f));

	sprite->setAnimationSpeed(HURT_RIGHT, 10);
	for (i = 0; i < 5; ++i)
		sprite->addKeyframe(HURT_RIGHT, glm::vec2((float(i) * 0.0625f), 0.6f));
	for (i = 0; i < 28; ++i)
		sprite->addKeyframe(HURT_RIGHT, glm::vec2(0.3125f, 0.6f));

	sprite->setAnimationSpeed(HURT_LEFT, 10);
	for (i = 0; i < 5; ++i)
		sprite->addKeyframe(HURT_LEFT, glm::vec2((float(i) * 0.0625f), 0.7f));
	for (i = 0; i < 28; ++i)
		sprite->addKeyframe(HURT_LEFT, glm::vec2(0.3125f, 0.7f));

	sprite->setAnimationSpeed(FALL_RIGHT, 10);
	for (i = 0; i < 5; ++i)
		sprite->addKeyframe(FALL_RIGHT, glm::vec2((float(i) * 0.0625f), 0.6f));
	for (i = 0; i < 28; ++i)
		sprite->addKeyframe(FALL_RIGHT, glm::vec2(0.3125f, 0.6f));

	sprite->setAnimationSpeed(FALL_LEFT, 10);
	for (i = 0; i < 5; ++i)
		sprite->addKeyframe(FALL_LEFT, glm::vec2((float(i) * 0.0625f), 0.7f));
	for (i = 0; i < 28; ++i)
		sprite->addKeyframe(FALL_LEFT, glm::vec2(0.3125f, 0.7f));
		

	sprite->changeAnimation(initAnim);
}
