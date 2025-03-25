#ifndef _SHIELD_INCLUDE
#define _SHIELD_INCLUDE

#include "Item.h"

class Shield : public Item
{

protected:
	void updateItem(int deltaTime);
	string getImagePath();
	void initSprites();

};

#endif
