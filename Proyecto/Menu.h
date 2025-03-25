#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Definitions.h"


#include "State.h"
#include "Sprite.h"
#include "Texture.h"
#include "SoundCtrl.h"
#include <vector>


class Menu : public State
{

public:
	static Menu &instance()
	{
		static Menu M;
		return M;
	};

	
	void init();
	void update(int deltaTime);
	void render();
	void pause();
	void unpause();

	void changeModeUp();
	void changeModeDown();
	int getMode();

private:
	void initTextures();
	void initSprites();
	void changeSprites();

	//Modos del menú:
	int mode; //0 -> play, 1 -> options, 2 -> credits, 3 -> exit
	int modeAnterior;
	bool bPaused;

	Texture menuTexture;
	Texture nightTexture;
	Texture knightTexture;
	Texture playTexture;
	Texture optionsTexture;
	Texture creditsTexture;
	Texture textsTex[4];

	Sprite* backgroundSprite;
	Sprite* nightSprite;
	Sprite* knightSprite;
	Sprite* playSprite;
	Sprite* optionsSprite;
	Sprite* creditsSprite;
	Sprite* texts[4];

	//Positions for text sprites:
	glm::vec2 positions[2] = {
		glm::vec2(0.f, 0.f),
		glm::vec2(0.f, 0.5f)
	};

	//const SoundCtrl* soundCtrl;
	//FMOD::Sound* music;
	//FMOD::Channel* channel;

};


#endif // _MENU_INCLUDE