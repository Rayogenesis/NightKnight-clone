#ifndef _DOOR_INCLUDE
#define _DOOR_INCLUDE

#include "Item.h"

class Door : public Item
{
public:
	bool collision();

protected:
	void initItem();
	void updateItem(int deltaTime);
	
	string getImagePath();
	void initSprites();

	int opening;
};

#endif

