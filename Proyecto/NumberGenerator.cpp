#include "NumberGenerator.h"

Sprite* NumberGenerator::createNum()
{
	Sprite* numSprite = Sprite::createSprite(glm::ivec2(15, 25), glm::vec2(1.f/10.f, 1.f), &numTexture, &TEX_PROGRAM);
	numSprite->setNumberAnimations(10);
	for (int i = 0; i < 10; ++i) {
		numSprite->addKeyframe(i, this->numPositions[i]);
	}
	return numSprite;
}

void NumberGenerator::initTexture()
{
	numTexture.loadFromFile("images/HUD/Numeros/nums.png", TEXTURE_PIXEL_FORMAT_RGBA);
	numTexture.setMinFilter(GL_NEAREST);
	numTexture.setMagFilter(GL_NEAREST);
}

Sprite* NumberGenerator::createSymbol(char symbol)
{
	Sprite* numSprite = Sprite::createSprite(glm::ivec2(7, 10), glm::vec2(38. / 256, 81. / 512), &numTexture, &TEX_PROGRAM);
	numSprite->setNumberAnimations(1);

	if (symbol == '-') {
		numSprite->addKeyframe(0, glm::vec2(0.5, 0.5));
		numSprite->changeAnimation(0);
	}
	else if (symbol == '%') {
		numSprite->addKeyframe(0, glm::vec2(0.75, 0.5));
		numSprite->changeAnimation(0);
	}
	else {
		delete numSprite;
	}

	return numSprite;
}


