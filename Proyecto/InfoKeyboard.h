#ifndef _INFOKEYBOARD_INCLUDE
#define _INFOKEYBOARD_INCLUDE

#include "StateCtrl.h"
#include "KeyboardCtrl.h"

class InfoKeyboard : public KeyboardCtrl
{

public:
	static InfoKeyboard& instance()
	{
		static InfoKeyboard IK;
		return IK;
	};


	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);


};
#endif // _INFOKEYBOARD_INCLUDE

