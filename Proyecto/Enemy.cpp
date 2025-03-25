#include "Enemy.h"

bool Enemy::collision()
{
	glm::ivec2 topLeft = getTopLeft();
	glm::ivec2 botRight = getBotRight();

	if (!(playerBotRight.x < topLeft.x || botRight.x < playerTopLeft.x) &&
		!(playerBotRight.y < topLeft.y || botRight.y < playerTopLeft.y))
	{
		changeHorizontalDirection();
		return true;
	}
	return false;
}