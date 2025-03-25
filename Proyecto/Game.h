#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Definitions.h"


#include "Scene.h"
#include "State.h"
#include "ShaderCtrl.h"
#include "Menu.h"

// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	static Game &instance()
	{
		static Game G;
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();

	State* getState();
	void setState(State* state);
	void setBplay(bool b);

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	//const SoundCtrl* getSoundController() const;

private:
	Game() {}

private:
	bool bPlay;                       // Continue to play game?
	State *state;                     // State to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	//SoundCtrl soundCtrl;              // we can have access at any time
};


#endif // _GAME_INCLUDE


