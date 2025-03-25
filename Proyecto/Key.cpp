#include "Key.h"

string Key::getImagePath()
{
	return "images/Items/Key/keyy.png";
}

void Key::initSprites()
{
	hitboxSize = glm::ivec2(15, 15);
	this->itemSprite = Sprite::createSprite(hitboxSize, glm::vec2(1.f, 1.f), &itemTex, &TEX_PROGRAM);
}


