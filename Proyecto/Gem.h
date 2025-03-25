#ifndef _GEM_INCLUDE
#define _GEM_INCLUDE

#include "Item.h"

class Gem : public Item
{
protected:
	void updateItem(int deltaTime);
	string getImagePath();
	void initSprites();
};

#endif

