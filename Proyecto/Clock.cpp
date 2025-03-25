#include "Clock.h"

string Clock::getImagePath()
{
	return "images/Items/Clock/relojj.png";
}

void Clock::updateItem(int deltaTime)
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

void Clock::initSprites()
{
	hitboxSize = glm::ivec2(15, 15);
	this->itemSprite = Sprite::createSprite(hitboxSize, glm::vec2(1.f, 1.f), &itemTex, &TEX_PROGRAM);
}
