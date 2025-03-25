#include "StateCtrl.h"
#include "Menu.h"
#include "Info.h"
#include "Game.h"
#include "ConfirmationDialog.h"

void StateCtrl::changeTo(State* st)
{
	SoundCtrl::instance().endMusic();
	st->init();
	Game::instance().setState(st);
}

void StateCtrl::changeToMenu()
{
	SoundCtrl::instance().endMusic();
	Menu::instance().init();
	Game::instance().setState(&Menu::instance());
}

void StateCtrl::changeStage(int stage, int pts, int h, int pg)
{
	SoundCtrl::instance().endMusic();
	Scene::instance().changeStage(stage);
	Scene::instance().init();
	Scene::instance().setPrevStats(pts, h, pg);
	Game::instance().setState(&Scene::instance());
}

void StateCtrl::pause(State* st)
{
	SoundCtrl::instance().pauseMusic();
	st->pause();
	Game::instance().setState(st);
}

void StateCtrl::unpause(State* st)
{
	SoundCtrl::instance().unpauseMusic();
	st->unpause();
	Game::instance().setState(st);
}

void StateCtrl::changeToDialog(State* st)
{
	ConfirmationDialog::instance().init();
	ConfirmationDialog::instance().setState(st);
	Game::instance().setState(&ConfirmationDialog::instance());
}



