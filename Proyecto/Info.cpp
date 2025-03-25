#include "Info.h"

void Info::init()
{
	initTextures();
	initSprites();
	initSounds();
	keyboardCtrl = &InfoKeyboard::instance();
}

void Info::initSounds()
{
	SoundCtrl::instance().putTrack("sounds/Menu/EzloAppears.mp3", 0.1f);
}

void Info::initTextures()
{
	//Cargamos Opciones:
	if (mode == 1) {
		imageTexture.loadFromFile("images/Menu/Options/imageOptions.png", TEXTURE_PIXEL_FORMAT_RGBA);
		imageTexture.setMinFilter(GL_NEAREST);
		imageTexture.setMagFilter(GL_NEAREST);
	}
	else { //Cargamos Credits:
		imageTexture.loadFromFile("images/Menu/Credits/imageCredits.png", TEXTURE_PIXEL_FORMAT_RGBA);
		imageTexture.setMinFilter(GL_NEAREST);
		imageTexture.setMagFilter(GL_NEAREST);
	}
}


void Info::initSprites()
{
	imageSprite = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT+100), glm::vec2(1.f, 1.f), &imageTexture, &TEX_PROGRAM);
	imageSprite->setPosition(glm::vec2(0, 0));
}

void Info::update(int deltaTime)
{
}

void Info::render()
{
	RENDER_SHADERS;
	imageSprite->render();
}

void Info::pause()
{
}

void Info::unpause()
{
}
