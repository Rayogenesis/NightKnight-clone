#include "Gem.h"

string Gem::getImagePath()
{
	return "images/Items/Gem/gemita.png";
}

void Gem::updateItem(int deltaTime)
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

void Gem::initSprites()
{
	hitboxSize = glm::ivec2(12, 16);
	this->itemSprite = Sprite::createSprite(hitboxSize, glm::vec2(0.1f, 1.f), &itemTex, &TEX_PROGRAM);

	this->itemSprite->setNumberAnimations(1);
	this->itemSprite->setAnimationSpeed(0, 4);
	for (int i = 0; i < 9; ++i) {
		this->itemSprite->addKeyframe(0, glm::vec2(0.1f*float(i), 0));
	}
	this->itemSprite->changeAnimation(0);
}
