#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	ShaderCtrl::instance().init();				// initShaders

	state = &Menu::instance();
	state->init();
}

void Game::setState(State* state)
{
	this->state = state;
}

bool Game::update(int deltaTime)
{
	state->update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	state->render();
}

State* Game::getState()
{
	return state;
}

void Game::setBplay(bool b)
{
	bPlay = b;
}


// Input callback methods
void Game::keyPressed(int key)
{
	state->getKeyboardCtrl()->keyPressed(key);
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	state->getKeyboardCtrl()->keyReleased(key);
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	state->getKeyboardCtrl()->specialKeyPressed(key);
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	state->getKeyboardCtrl()->specialKeyReleased(key);
	specialKeys[key] = false;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

//const SoundCtrl* Game::getSoundController() const {
//	return &soundCtrl;
//}