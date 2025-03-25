#include "ConfirmationDialog.h"
#include <iostream>

void ConfirmationDialog::init()
{
	initTextures();
	initSprites();
	mode = 0;
	keyboardCtrl = &DialogKeyboard::instance();
}

void ConfirmationDialog::initTextures()
{
	imageTexture.loadFromFile("images/HUD/Dialogo/confirmationDialogs.png", TEXTURE_PIXEL_FORMAT_RGBA);
	imageTexture.setMinFilter(GL_NEAREST);
	imageTexture.setMagFilter(GL_NEAREST);
}


void ConfirmationDialog::initSprites()
{
	imageSprite = Sprite::createSprite(glm::vec2(300, 150), glm::vec2(1.f, 0.5f), &imageTexture, &TEX_PROGRAM);
	imageSprite->setPosition(glm::vec2((SCREEN_WIDTH/2.f)-140, (SCREEN_HEIGHT/2.f)-90));
	
	imageSprite->setNumberAnimations(2);
	glm::vec2 positions[2] = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.5f)};
	for (int j = 0; j < 2; ++j) {
		imageSprite->addKeyframe(j, positions[j]);
	}
}

void ConfirmationDialog::update(int deltaTime)
{
	changeSprites();
}

void ConfirmationDialog::changeSprites()
{
	imageSprite->changeAnimation(mode);
}

void ConfirmationDialog::changeModeRight()
{
	if (mode == 0) mode = 1;
}

void ConfirmationDialog::changeModeLeft()
{
	if (mode == 1) mode = 0;
}

void ConfirmationDialog::render()
{
	RENDER_SHADERS;
	//Renderizamos el estado que queremos tener de fondo.
	state->render();

	//Renderizamos el cuadro de diálogo.
	imageSprite->render();
}

void ConfirmationDialog::setState(State* st)
{
	this->state = st;
}


State* ConfirmationDialog::getState()
{
	return state;
}

int ConfirmationDialog::getMode()
{
	return mode;
}

void ConfirmationDialog::pause()
{
}

void ConfirmationDialog::unpause()
{
}


