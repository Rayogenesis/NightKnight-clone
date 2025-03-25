#ifndef _STATE_INCLUDE
#define _STATE_INCLUDE


#include "KeyboardCtrl.h"
#include "SoundCtrl.h"


class State
{

public:

	virtual void init() = 0;					// = 0 so that the class
	virtual void update(int deltaTime) = 0;		// is pure virtual
	virtual void render() = 0;					// (abstract)
	virtual void pause() = 0;
	virtual void unpause() = 0;
	virtual int getMode() const { return 0; };

	bool isPaused() { return bPaused; }

	KeyboardCtrl *getKeyboardCtrl();

protected:
	KeyboardCtrl *keyboardCtrl;
	bool bPaused;

};


#endif // _STATE_INCLUDE