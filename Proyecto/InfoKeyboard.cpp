#include <GL/glew.h>
#include <GL/glut.h>
#include "InfoKeyboard.h"
#include "Game.h"


void InfoKeyboard::keyPressed(int key)
{
	//If esc is pressed, return to Menu.
	if (key == 27 || key == 13) {
		StateCtrl::instance().changeTo(&Menu::instance());
	}
	if (key == 'm' || key == 'M')
	{
		SoundCtrl::instance().pressM();
		SoundCtrl::instance().endMusic();
	}
	if (key == '1' || key == '2' || key == '3')
		StateCtrl::instance().changeStage(key - 48, 0, 3, 1000);
}

void InfoKeyboard::keyReleased(int key)
{

}

void InfoKeyboard::specialKeyPressed(int key)
{

}

void InfoKeyboard::specialKeyReleased(int key)
{

}
