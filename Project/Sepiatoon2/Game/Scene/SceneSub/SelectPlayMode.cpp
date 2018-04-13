#include"SelectPlayMode.h"

#include"Manual.cpp"

SelectPlayMode::SelectPlayMode()
{
	scene_name = L"SelectPlayMode";
	initialize();
}

SelectPlayMode::~SelectPlayMode()
{
	finalize();
}

void SelectPlayMode::initialize()
{

}

void SelectPlayMode::finalize()
{

}

void SelectPlayMode::enter()
{

}

void SelectPlayMode::exit()
{

}

void SelectPlayMode::update()
{

}

void SelectPlayMode::draw()
{

}

void SelectPlayMode::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new SelectMap());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new Manual());
	}
}

void SelectPlayMode::debug_draw()
{

}