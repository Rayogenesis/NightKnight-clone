#ifndef _KEY_INCLUDE
#define _KEY_INCLUDE

#include "Item.h"

class Key : public Item
{

protected:
	string getImagePath();
	void initSprites();

};

#endif

