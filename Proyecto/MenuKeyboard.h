#ifndef _MENUKEYBOARD_INCLUDE
#define _MENUKEYBOARD_INCLUDE

#include "KeyboardCtrl.h"

class MenuKeyboard : public KeyboardCtrl
{

public:
	static MenuKeyboard& instance()
	{
		static MenuKeyboard MK;
		return MK;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);

};
#endif // _MENUKEYBOARD_INCLUDE