#ifndef _DIALOGKEYBOARD_INCLUDE 
#define _DIALOGKEYBOARD_INCLUDE

#include "StateCtrl.h"
#include "KeyboardCtrl.h"

class DialogKeyboard : public KeyboardCtrl
{

public:
	static DialogKeyboard& instance()
	{
		static DialogKeyboard DK;
		return DK;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);


};
#endif // _DIALOGKEYBOARD_INCLUDE

