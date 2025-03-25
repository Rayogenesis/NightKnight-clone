#ifndef _PUNTUACIONDISPLAY_INCLUDE
#define _PUNTUACIONDISPLAY_INCLUDE


#include "NumberGenerator.h"
#include <vector>

class PuntuacionDisplay 
{
public:
	void init(int sizeNumbers);
	void displayNum(int num);
	void render();
	void setPosition(glm::vec2 position);

private:
	vector<Sprite*> numbers;
};

#endif //_PUNTUACIONDISPLAY_INCLUDE

