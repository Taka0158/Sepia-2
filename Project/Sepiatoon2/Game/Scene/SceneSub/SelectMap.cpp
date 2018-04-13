#include"SelectMap.h"

#include"SelectPlayMode.cpp"

SelectMap::SelectMap()
{
	scene_name = L"SelectMap";
	initialize();
}

SelectMap::~SelectMap()
{
	finalize();
}

void SelectMap::initialize()
{

}

void SelectMap::finalize()
{

}

void SelectMap::enter()
{

}

void SelectMap::exit()
{

}

void SelectMap::update()
{

}

void SelectMap::draw()
{

}

void SelectMap::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new SelectWeapon());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectPlayMode());
	}
}

void SelectMap::debug_draw()
{

}