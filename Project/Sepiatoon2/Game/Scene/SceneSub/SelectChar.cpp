#include"SelectChar.h"

#include"SelectWeapon.cpp"

SelectChar::SelectChar()
{
	scene_name = L"SelectChar";
	initialize();
}

SelectChar::~SelectChar()
{
	finalize();
}

void SelectChar::initialize()
{

}

void SelectChar::finalize()
{

}

void SelectChar::enter()
{

}

void SelectChar::exit()
{

}

void SelectChar::update()
{

}

void SelectChar::draw()
{

}

void SelectChar::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new Title());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectWeapon());
	}

}

void SelectChar::debug_draw()
{

}