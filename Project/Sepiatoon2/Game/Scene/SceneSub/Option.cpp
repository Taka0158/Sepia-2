#include"Option.h"

Option::Option()
{
	scene_name = L"Option";
	initialize();
}

Option::~Option()
{
	finalize();
}

void Option::initialize()
{

}

void Option::finalize()
{

}

void Option::enter()
{

}

void Option::exit()
{

}

void Option::update()
{
}

void Option::draw()
{
}

void Option::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new Title());
	}
}

void Option::debug_draw()
{

}