#ifndef _STATECTRL_INCLUDE
#define _STATECTRL_INCLUDE


#include "State.h"

class StateCtrl
{

public:

	static StateCtrl &instance()
	{
		static StateCtrl SC;
		return SC;
	};

	void changeTo(State* st);
	void changeToMenu();
	void changeStage(int stage, int pts, int h, int pg);
	void changeToDialog(State* st);
	void pause(State* st);
	void unpause(State* st);
};


#endif // _STATECTRL_INCLUDE
