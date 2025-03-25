#ifndef _DIALOG_INCLUDE 
#define _DIALOG_INCLUDE

#include "Definitions.h"

#include "State.h"
#include "Sprite.h"
#include "Texture.h"
#include "DialogKeyboard.h"

class ConfirmationDialog : public State
{	
public:
	static ConfirmationDialog &instance()
	{
		static ConfirmationDialog CD;
		return CD;
	};
	
	void update(int deltaTime);
	void init();
	void render();
	void pause();
	void unpause();

	void setState(State* st);
	State* getState();
	int getMode();
	void changeModeLeft();
	void changeModeRight();

private:
	void initTextures();
	void initSprites();
	void changeSprites();

	Texture imageTexture;
	Sprite* imageSprite;

	int mode;
	State* state;
}; 

#endif //_DIALOG_INCLUDE

