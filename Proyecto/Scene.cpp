#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Scene.h"

#include "SceneKeyboard.h"
#include "Game.h"
#include "NumberGenerator.h"
#include "HUD.h"
#include "Key.h"
#include "Gem.h"
#include "StateCtrl.h"


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (lvl != NULL)
		delete lvl;
	if(player != NULL)
		delete player;
	if (backgSprite != NULL)
		delete backgSprite;
	if (backBlack != NULL)
		delete backBlack;
}

void Scene::init()
{
	if (stage == 0) stage = 1;

	SoundCtrl::instance().putTrack("sounds/Scene/VaatiTheme.mp3", 0.1f);

	initMap();
	initTextures();
	initBackground();

	initLvl();
	initPlayer();
	initEnemies();
	
	bPaused = true;
	gameOver = false;
	musicChanged = false;
	pauseDuration = 2800;
	deathDuration = 2800;
	gameOverDuration = 4800;

	currentTime = 0.0f;
	timerCooldown = 1000;
	timer = 60;
	timeToPoints = 250;
	timeToPointsDuration = 2000;
	winDuration = 2000;
	winScreen = false;
	winScreenDuration = 4800;
	initHUD();
	initItems();

	keyboardCtrl = &SceneKeyboard::instance();
}

void Scene::update(int deltaTime)
{
	if (gameOver) {
		if (gameOverDuration > 0) {
			gameOverDuration -= deltaTime;
			if (gameOverDuration <= 0)
			{
				StateCtrl::instance().changeToMenu();
			}
		}
	}
	else if (winScreen)
	{
		if (winScreenDuration > 0) {
			winScreenDuration -= deltaTime;
			if (winScreenDuration <= 0)
			{
				StateCtrl::instance().changeToMenu();
			}
		}
	}
	else if (player->getHealth() == 0) {
		if (!musicChanged) {
			//Pausar música de escena.
			SoundCtrl::instance().endMusic();
			musicChanged = true;
		}
		if (deathDuration > 0) {
			player->update(deltaTime);
			deathDuration -= deltaTime;
			if (deathDuration <= 0)
			{
				SoundCtrl::instance().putTrack("sounds/GameOver/GameOver.mp3", 0.1f);
				gameOver = true;
			}
		}
	}
	else if (player->hasWon())
	{
		if (winDuration > 0) {
			winDuration -= deltaTime;
		}
		else
		{
			if (timer == 0)
			{
				timeToPointsDuration -= deltaTime;
				if (timeToPointsDuration <= 0) {
					if (stage < 3)
						StateCtrl::instance().changeStage(stage + 1, player->getPuntuacion(), player->getHealth(), player->getPuntGoal());
					else {
						winScreen = true;
						SoundCtrl::instance().putSFX("sounds/SFX/win.wav", 0.2f);
					}
				}
			}
			else
			{
				timeToPoints -= deltaTime;
				if (timeToPoints <= 0) {
					SoundCtrl::instance().putSFX("sounds/SFX/sumar_puntos.wav", 0.2f);
					timer -= 1;
					timeToPoints = 100;
					player->givePoints(10);
					player->update(deltaTime);
					updateHUD();
				}
			}
		}
	}
	else if (!bPaused)
	{
		currentTime += deltaTime;
		player->update(deltaTime);
		updateItems(deltaTime);
		updateEnemies(deltaTime);
		if (!player->hasClock()) updateTimer(deltaTime);
		updateHUD();
		
		if (player->getHealth() == 0 || player->hasWon())
		{
			if (player->hasWon())
			{
				player->unpaint();
				SoundCtrl::instance().endMusic();
				SoundCtrl::instance().putSFX("sounds/SFX/stageClear.wav", 0.2f);
			}
			unpaintEnemies();
			unpaintItems();
		}
	}
	else
	{
		if (pauseDuration <= 2800)
		{
			pauseDuration -= deltaTime;
			if (pauseDuration <= 0)
			{
				bPaused = false;
				pauseDuration = 4000;
			}
		}
	}
}

void Scene::render()
{
	RENDER_SHADERS;
	backBlack->render();

	if (!gameOver && !winScreen) {
		backgSprite->render();
		ShaderCtrl::instance().setTranslateModelview();
		map->render();
		if (bPaused) readySprite->render();
		if (player->isGodMode()) godModeSprite->render();
		if (player->hasWon()) stClearSprite->render();
		renderItems();
		if (player->bePainted()) player->render();
		renderEnemies();

		HUD::instance().render();
	}
	else if (gameOver) {
		gameOverSprite->render();
	}
	else if (winScreen) {
		winSprite->render();
	}
}

void Scene::flipGodMode() {
	if (!bPaused)
		player->flipGodMode();
}

void Scene::giveKey() {
	if (!bPaused)
		player->takeItem('K');
}

void Scene::setPrevStats(int pts, int h, int pg) {
	player->givePoints(pts);
	player->setHealth(h);
	player->setPuntGoal(pg);
	HUD::instance().update(player->getHealth(), player->getPuntuacion(), timer, stage);
}

void Scene::initMap()
{
	map = TileMap::createTileMap("levels/tilemap0" + std::to_string(stage) + ".txt",
								 glm::vec2(SCREEN_X, SCREEN_Y), TEX_PROGRAM);
}

void Scene::initLvl()
{
	lvl = Level::createLevel("levels/level0" + std::to_string(stage) + ".txt");
}

void Scene::initPlayer()
{
	player = new Player();
	player->init(map, glm::ivec2(SCREEN_X + TRANSLATE.x, SCREEN_Y + TRANSLATE.y),
				 glm::ivec2(map->getTileSizeX() * lvl->getInitPlayerPosX(), map->getTileSizeY() * lvl->getInitPlayerPosY()),
				 lvl->getInitPlayerAnim(), TEX_PROGRAM);
}

void Scene::initEnemies()
{
	enemies = lvl->getEnemies();
	for (Enemy* enemy : *enemies)
		enemy->init(map, glm::ivec2(SCREEN_X + TRANSLATE.x, SCREEN_Y + TRANSLATE.y),
					glm::ivec2(map->getTileSizeX() * enemy->getInitTileX(), map->getTileSizeY() * enemy->getInitTileY()),
					enemy->getInitAnim(), TEX_PROGRAM);
}

void Scene::updateEnemies(int deltaTime)
{
	glm::ivec2 playerTopLeft = player->getTopLeft();
	glm::ivec2 playerBotRight = player->getBotRight();

	for (Enemy* enemy : *enemies)
	{
		if (player->getHealth() > 0)
		{
			enemy->setPlayerTopLeft(playerTopLeft);
			enemy->setPlayerBotRight(playerBotRight);

			if (!player->hasClock()) enemy->update(deltaTime);

			if (!player->isHurt() && !player->isGodMode() && enemy->collision())
				player->hit();
		}
	}
}

void Scene::renderEnemies()
{
	for (Enemy* enemy : *enemies)
		if (enemy->bePainted()) enemy->render();
}

void Scene::unpaintEnemies()
{
	for (Enemy* enemy : *enemies)
		enemy->unpaint();
}

void Scene::initItems()
{
	items = lvl->getItems();
	for (Item* item : *items) {
		item->init();
	}
}

void Scene::updateItems(int deltaTime)
{
	glm::ivec2 playerTopLeft = player->getTopLeft();
	glm::ivec2 playerBotRight = player->getBotRight();

	for (Item* item : *items) {
		if (player->getHealth() > 0 && !item->isTaken())
		{
			item->setPlayerTopLeft(playerTopLeft);
			item->setPlayerBotRight(playerBotRight);

			if (item->getType() == 'K' && map->getNumTilesPisables() == 0)
				item->changeBPaint(true);

			else if (item->getType() == 'D' && player->hasKey())
				item->setTimeToAppear(0); // la puerta se abre

			if (!player->hasClock() || item->getType() == 'D') item->update(deltaTime);

			if (item->getBPaint() && item->collision()) {
				player->takeItem(item->getType());
			}
		}
	}
}

void Scene::renderItems()
{
	for (Item* item : *items) {
		item->render();
	}
}

void Scene::unpaintItems()
{
	for (Item* item : *items)
		item->changeBPaint(false);
}

void Scene::initHUD()
{
	HUD::instance().init();
	HUD::instance().update(player->getHealth(), player->getPuntuacion(), timer, stage);
}

void Scene::updateHUD()
{
	HUD::instance().setShield(player->hasShield());
	HUD::instance().update(player->getHealth(), player->getPuntuacion(), timer, stage);
}

void Scene::updateTimer(int deltaTime)
{
	timerCooldown -= deltaTime;
	if (timerCooldown <= 0) {
		timer -= 1;
		timerCooldown = 1000;
	}

	if (timer == 0)
	{
		if (player->getHealth() > 0)
			player->hit();

		if (player->getHealth() > 0)
			timer = 60;
	}
}

void Scene::initTextures()
{
	backgTexture.loadFromFile("images/Scene/Background/fondoPLSPLS.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgTexture.setMinFilter(GL_NEAREST);
	backgTexture.setMagFilter(GL_NEAREST);

	backBlackTexture.loadFromFile("images/Scene/Background/fondoBlack.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backBlackTexture.setMinFilter(GL_NEAREST);
	backBlackTexture.setMagFilter(GL_NEAREST);

	readyTex.loadFromFile("images/HUD/Ready/readyy.png", TEXTURE_PIXEL_FORMAT_RGBA);
	readyTex.setMinFilter(GL_NEAREST);
	readyTex.setMagFilter(GL_NEAREST);

	gameOverTex.loadFromFile("images/HUD/GameOver/gameOver.png", TEXTURE_PIXEL_FORMAT_RGBA);
	gameOverTex.setMinFilter(GL_NEAREST);
	gameOverTex.setMagFilter(GL_NEAREST);

	winTex.loadFromFile("images/HUD/youWin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	winTex.setMinFilter(GL_NEAREST);
	winTex.setMagFilter(GL_NEAREST);

	stClearTex.loadFromFile("images/HUD/stageClear.png", TEXTURE_PIXEL_FORMAT_RGBA);
	stClearTex.setMinFilter(GL_NEAREST);
	stClearTex.setMagFilter(GL_NEAREST);

	godModeTex.loadFromFile("images/HUD/GodMode/gloriousWhite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	godModeTex.setMinFilter(GL_NEAREST);
	godModeTex.setMagFilter(GL_NEAREST);
}


void Scene::initBackground()
{
	backgSprite = Sprite::createSprite(glm::vec2((TILESIZE.x * map->getMapSize().x) - 1, TILESIZE.y * map->getMapSize().y), glm::vec2(1.f, 1.f), &backgTexture, &TEX_PROGRAM);
	backgSprite->setPosition(glm::vec2(SCREEN_X+TRANSLATE.x, SCREEN_Y+TRANSLATE.y));

	backBlack = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &backBlackTexture, &TEX_PROGRAM);	
	backBlack->setPosition(glm::vec2(0,0));

	//Ready sprite:
	readySprite = Sprite::createSprite(glm::vec2(160, 80), glm::vec2(1.f, 1.f), &readyTex, &TEX_PROGRAM);	
	readySprite->setPosition(glm::vec2(SCREEN_WIDTH/2.f - 80.f, SCREEN_HEIGHT/2.f - 40.f));

	//Game Over sprite:
	gameOverSprite = Sprite::createSprite(glm::vec2(180, 50), glm::vec2(1.f, 1.f), &gameOverTex, &TEX_PROGRAM);	
	gameOverSprite->setPosition(glm::vec2(SCREEN_WIDTH/2.f - 90.f, SCREEN_HEIGHT/2.f - 25.f));

	//Win sprite
	winSprite = Sprite::createSprite(glm::vec2(180, 50), glm::vec2(1.f, 1.f), &winTex, &TEX_PROGRAM);	
	winSprite->setPosition(glm::vec2(SCREEN_WIDTH/2.f - 90.f, SCREEN_HEIGHT/2.f - 25.f));

	//Stage clear sprite
	stClearSprite = Sprite::createSprite(glm::vec2(190, 80), glm::vec2(1.f, 1.f), &stClearTex, &TEX_PROGRAM);	
	stClearSprite->setPosition(glm::vec2(SCREEN_WIDTH/2.f - 95.f, SCREEN_HEIGHT/2.f - 40.f));

	//God Mode sprite:
	godModeSprite = Sprite::createSprite(glm::vec2(120, 50), glm::vec2(1.f, 1.f), &godModeTex, &TEX_PROGRAM);
	godModeSprite->setPosition(glm::vec2(330, 15));
}

