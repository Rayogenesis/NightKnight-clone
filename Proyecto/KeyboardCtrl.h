#ifndef _KEYBOARDCTRL_INCLUDE
#define _KEYBOARDCTRL_INCLUDE


class KeyboardCtrl
{

public:
	virtual void keyPressed(int key) = 0;
	virtual void keyReleased(int key) = 0;
	virtual void specialKeyPressed(int key) = 0;
	virtual void specialKeyReleased(int key) = 0;

};
#endif // _KEYBOARDCTRL_INCLUDE