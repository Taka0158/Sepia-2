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
	OBJ_MGR->update();
}

void Title::draw()
{
	OBJ_MGR->draw();
}

void Title::debug_update()
{
	if (Input::MouseL.clicked)
	{
		OBJ_MGR->create_TestObj(Mouse::Pos());
	}
	if (Input::MouseR.clicked)
	{
		MSG_DIS->dispatch_message(0.0, ID_MGR_SCENE, ID_MGR_OBJ, msg::TYPE::OBJMGR_DESTROY_ALL_OBJECT);
	}

	if (Input::Key1.clicked)
	{
		OBJ_MGR->finalize();
		SCENE_MGR->change_scene(new Option());
	}
	else if (Input::Key2.clicked)
	{
		OBJ_MGR->finalize();
		SCENE_MGR->change_scene(new SelectChar());
	}
	OBJ_MGR->debug_update();
}

void Title::debug_draw()
{
	OBJ_MGR->debug_draw();
}

