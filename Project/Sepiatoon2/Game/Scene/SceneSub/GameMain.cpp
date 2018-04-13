#include"GameMain.h"

#include"Result.cpp"

GameMain::GameMain()
{
scene_name = L"GameMain";
initialize();
}

GameMain::~GameMain()
{
finalize();
}

void GameMain::initialize()
{

}

void GameMain::finalize()
{

}

void GameMain::enter()
{

}

void GameMain::exit()
{

}

void GameMain::update()
{

}

void GameMain::draw()
{

}

void GameMain::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new Result());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new Title());
	}
	else if (Input::Key3.clicked)
	{
		SCENE_MGR->change_scene(new SelectChar());
	}
	else if (Input::Key4.clicked)
	{
		SCENE_MGR->change_scene(new SelectWeapon());
	}
	else if (Input::Key5.clicked)
	{
		SCENE_MGR->change_scene(new SelectPlayMode());
	}
	else if (Input::Key6.clicked)
	{
		SCENE_MGR->change_scene(new GameMain());
	}
}

void GameMain::debug_draw()
{

}