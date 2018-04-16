#include"TestWorld.h"

TestWorld::TestWorld()
{
	m_ui = UI_MGR;
	scene_name = L"TestWorld";
	initialize();
}

TestWorld::~TestWorld()
{
	finalize();
}

void TestWorld::initialize()
{
	finalize();
	OBJ_MGR->initialize();
	SCENE_CAMERA->initialize();
	m_ui->initialize();
}

void TestWorld::finalize()
{
	OBJ_MGR->finalize();
	SCENE_CAMERA->finalize();
	m_ui->finalize();
	MSG_DIS->destroy_all_message();
}

void TestWorld::enter()
{

}

void TestWorld::exit()
{

}

void TestWorld::update()
{
	OBJ_MGR->update();
	//EFFECT_MGR->update();
	OBJ_MGR->debug_update();

}

void TestWorld::draw()
{
	//ƒJƒƒ‰‚Ì‰e‹¿‰º
	SCENE_CAMERA->update();
	{
		const auto t1 = SCENE_CAMERA->createTransformer();

		OBJ_MGR->draw();
		//EFFECT_MGR->draw();
		OBJ_MGR->debug_draw();
	}

}

void TestWorld::debug_update()
{
	if (Input::MouseM.pressed)
	{
		OBJ_MGR->create_TestObj(SCENE_CAMERA->get_mouse_pos());
	}
	if (Input::MouseR.clicked)
	{
		//MSG_DIS->dispatch_message(0.0, ID_MGR_SCENE, ID_MGR_OBJ, msg::TYPE::OBJMGR_DESTROY_ALL_OBJECT);
	}
	if (Input::KeyF1.clicked)
	{
		initialize();
		DEBUG->regist(DebugText(5, L"‰Šú‰»"));
	}
	if (Input::KeyF2.clicked)
	{
		OBJ_MGR->set_map(MapType::SIMPLE);
	}
	if (Input::KeyF3.clicked)
	{
		OBJ_MGR->destroy_map();
	}
}

void TestWorld::debug_draw()
{

}