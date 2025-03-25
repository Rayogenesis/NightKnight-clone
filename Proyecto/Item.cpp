#include "Item.h"


void Item::init()
{
	timeToDisappear = 10000;
	initTextures();
	initSprites();
	setPosition();
	bPaint = false;
	taken = false;
	initItem();
}

void Item::update(int deltaTime)
{
	updateItem(deltaTime);
	itemSprite->update(deltaTime);
}

void Item::render()
{
	if (bPaint) itemSprite->render();
}

void Item::initTextures()
{	
	itemTex.loadFromFile(getImagePath(), TEXTURE_PIXEL_FORMAT_RGBA);
	itemTex.setMinFilter(GL_NEAREST);
	itemTex.setMagFilter(GL_NEAREST);
}

void Item::setPosition()
{
	glm::ivec2 tileMapDispl = glm::ivec2(SCREEN_X + TRANSLATE.x, SCREEN_Y + TRANSLATE.y);
	position = glm::ivec2(initTile.x * TILESIZE.x, initTile.y * TILESIZE.y - hitboxSize.y);
	this->itemSprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

bool Item::collision()
{
	glm::ivec2 topLeft = getTopLeft();
	glm::ivec2 botRight = getBotRight();

	if (!(playerBotRight.x < topLeft.x || botRight.x < playerTopLeft.x) &&
		!(playerBotRight.y < topLeft.y || botRight.y < playerTopLeft.y))
	{
		bPaint = false;
		taken = true;
		return true;
	}
	return false;
}