#include "ShaderCtrl.h"

// Game
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Scene & TileMap
#define SCREEN_X 32
#define SCREEN_Y 16
#define TILESIZE glm::ivec2(32, 16) 

// ShaderCtrl
#define RENDER_SHADERS ShaderCtrl::instance().render()
#define TEX_PROGRAM ShaderCtrl::instance().getTexProgram()

//Camera
#define TRANSLATE glm::vec3(30, 60, 0)
