#include "Shield.h"

string Shield::getImagePath()
{
	return "images/Items/Shield/shield.png";
}

void Shield::updateItem(int deltaTime)
{
	if (timeToAppear > 0)
	{
		timeToAppear -= deltaTime;
		if (timeToAppear <= 0) bPaint = true;
	}
	else if (timeToDisappear > 0)
	{
		timeToDisappear -= deltaTime;
		if (timeToDisappear <= 0) bPaint = false;
	}
}

void Shield::initSprites()
{
	hitboxSize = glm::ivec2(14, 14);
	this->itemSprite = Sprite::createSprite(hitboxSize, glm::vec2(1.f, 1.f), &itemTex, &TEX_PROGRAM);
}