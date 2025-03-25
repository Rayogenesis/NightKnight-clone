#ifndef _SCENEKEYBOARD_INCLUDE
#define _SCENEKEYBOARD_INCLUDE


#include "StateCtrl.h"
#include "KeyboardCtrl.h"


class SceneKeyboard : public KeyboardCtrl
{

public:
	static SceneKeyboard& instance()
	{
		static SceneKeyboard SK;
		return SK;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);


};
#endif // _SCENEKEYBOARD_INCLUDE