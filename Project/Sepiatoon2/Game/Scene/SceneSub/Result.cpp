#include"Result.h"

Result::Result()
{
	scene_name = L"Result";
	initialize();
}

Result::~Result()
{
	finalize();
}

void Result::initialize()
{

}

void Result::finalize()
{

}

void Result::enter()
{

}

void Result::exit()
{

}

void Result::update()
{

}

void Result::draw()
{

}

void Result::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new Title());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectChar());
	}
	else if (Input::Key3.clicked)
	{
		SCENE_MGR->change_scene(new SelectWeapon());
	}
	else if (Input::Key4.clicked)
	{
		SCENE_MGR->change_scene(new SelectPlayMode());
	}
	else if (Input::Key5.clicked)
	{
		SCENE_MGR->change_scene(new GameMain());
	}
}

void Result::debug_draw()
{

}