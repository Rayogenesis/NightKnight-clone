#include <GL/glew.h>
#include <GL/glut.h>
#include "DialogKeyboard.h"
#include "Game.h"
#include "ConfirmationDialog.h"

void DialogKeyboard::keyPressed(int key)
{
	State* st = ConfirmationDialog::instance().getState();
	int mode = ConfirmationDialog::instance().getMode();

	//Escape o enter al No.
	if (key == 27 || (key == 13 && mode == 1)) {
		StateCtrl::instance().unpause(st);
	}
	//Enter al Yes.
	else if (key == 13 && mode == 0) {
		//Si estamos en Menu, salimos del juego.
		if (st == &Menu::instance()) Game::instance().setBplay(false);

		//Si no, volvemos al Menu.
		else StateCtrl::instance().changeTo(&Menu::instance());
	}
	if (key == 'm' || key == 'M')
	{
		SoundCtrl::instance().pressM();
		SoundCtrl::instance().endMusic();
	}
	if (key == '1' || key == '2' || key == '3')
		StateCtrl::instance().changeStage(key - 48, 0, 3, 1000);
}

void DialogKeyboard::keyReleased(int key)
{

}

void DialogKeyboard::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_RIGHT) {
		ConfirmationDialog::instance().changeModeRight();
	}
	else if (key == GLUT_KEY_LEFT) {
		ConfirmationDialog::instance().changeModeLeft();
	}
}

void DialogKeyboard::specialKeyReleased(int key)
{

}
