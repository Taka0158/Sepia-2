#include"Manual.h"

#include"GameMain.cpp"

Manual::Manual()
{
	scene_name = L"Manual";
	initialize();
}

Manual::~Manual()
{
	finalize();
}

void Manual::initialize()
{

}

void Manual::finalize()
{

}

void Manual::enter()
{

}

void Manual::exit()
{

}

void Manual::update()
{

}

void Manual::draw()
{

}

void Manual::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new GameMain());
	}
}

void Manual::debug_draw()
{

}