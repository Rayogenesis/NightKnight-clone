#ifndef _NUMBERGENERATOR_INCLUDE 
#define _NUMBERGENERATOR_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "Texture.h"
#include "Definitions.h"

class NumberGenerator
{
public:

	static NumberGenerator& instance()
	{
		static NumberGenerator NG; 
		return NG;
	};

	Sprite* createNum();
	Sprite* createSymbol(char symbol);
	void initTexture();

private:
	glm::vec2 numPositions[10] = {
		glm::vec2(0, 0),
		glm::vec2(1.f/10.f, 0),
		glm::vec2(2.f/10.f, 0),
		glm::vec2(3.f/10.f, 0),
		glm::vec2(4.f/10.f, 0),
		glm::vec2(5.f/10.f, 0),
		glm::vec2(6.f/10.f, 0),
		glm::vec2(7.f/10.f, 0),
		glm::vec2(8.f/10.f, 0),
		glm::vec2(9.f/10.f, 0)
	};

	Texture numTexture;
};



#endif //_NUMBERGENERATOR_INCLUDE

