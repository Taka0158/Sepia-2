#include"Title.h"

#include"Option.cpp"
#include"SelectChar.cpp"

Title::Title()
{
	scene_name = L"Title";
	initialize();
}

Title::~Title()
{
	finalize();
}

void Title::initialize()
{
}

void Title::finalize()
{
}

void Title::enter()
{				 

}

void Title::exit()
{

}

void Title::update()
{

}

void Title::draw()
{

}

void Title::debug_update()
{

	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new Option());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectChar());
	}
}

void Title::debug_draw()
{
	FontAsset(L"font_debug_8")(L"Title").drawCenter(Vec2(Setting::sc_w / 2, Setting::sc_h / 2));
}

