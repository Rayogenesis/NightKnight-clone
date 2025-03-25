#include "Door.h"
#include "SoundCtrl.h"


void Door::initItem()
{
	bPaint = true;
	opening = 1400;
}

void Door::updateItem(int deltaTime)
{
	if (timeToAppear == 0)
	{
		if (itemSprite->animation() == 0)
		{
			itemSprite->changeAnimation(1);
			SoundCtrl::instance().putSFX("sounds/SFX/door_open.wav", 0.2f);
		}
		else if (itemSprite->animation() == 1)
		{
			if (opening >= 0)
				opening -= deltaTime;
			else itemSprite->changeAnimation(2);
		}
	}
}

bool Door::collision()
{
	glm::ivec2 topLeft = getTopLeft();
	glm::ivec2 botRight = getBotRight();

	if (!(playerBotRight.x < topLeft.x || botRight.x < playerTopLeft.x) &&
		!(playerBotRight.y < topLeft.y || botRight.y < playerTopLeft.y) &&
		timeToAppear == 0)
	{
		bPaint = false;
		taken = true;
		return true;
	}
	return false;
}

string Door::getImagePath()
{
	return "images/Items/Door/door.png";
}

void Door::initSprites()
{
	hitboxSize = glm::ivec2(25, 31);
	this->itemSprite = Sprite::createSprite(hitboxSize, glm::vec2(0.125f, 1.f), &itemTex, &TEX_PROGRAM);

	this->itemSprite->setNumberAnimations(3);

	this->itemSprite->setAnimationSpeed(0, 4);
	this->itemSprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	this->itemSprite->setAnimationSpeed(1, 4);
	for (int i = 0; i < 6; ++i) {
		this->itemSprite->addKeyframe(1, glm::vec2(0.125f * float(i), 0.f));
	}

	this->itemSprite->setAnimationSpeed(2, 4);
	this->itemSprite->addKeyframe(2, glm::vec2(0.625f, 0.f));

	this->itemSprite->changeAnimation(0);
}