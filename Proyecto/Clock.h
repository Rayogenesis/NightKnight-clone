#ifndef _CLOCK_INCLUDE
#define _CLOCK_INCLUDE

#include "Item.h"

class Clock : public Item
{

protected:
	void updateItem(int deltaTime);
	string getImagePath();
	void initSprites();

}; 

#endif

