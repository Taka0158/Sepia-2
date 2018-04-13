#include"SelectWeapon.h"

#include"SelectMap.cpp"

SelectWeapon::SelectWeapon()
{
	scene_name = L"SelectWeapon";
	initialize();
}

SelectWeapon::~SelectWeapon()
{
	finalize();
}

void SelectWeapon::initialize()
{

}

void SelectWeapon::finalize()
{

}

void SelectWeapon::enter()
{

}

void SelectWeapon::exit()
{

}

void SelectWeapon::update()
{

}

void SelectWeapon::draw()
{

}

void SelectWeapon::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new SelectChar());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectMap());
	}
}

void SelectWeapon::debug_draw()
{

}