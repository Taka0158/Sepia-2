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

	if (Input::KeyF5.clicked)
	{
		OBJ_MGR->create_Ika();
	}
	if (Input::KeyF6.clicked)
	{
		OBJ_MGR->create_Ika(Vec2(400,400),
			Setting::get_controller_3(),
			Setting::get_color_B(),
			Setting::get_ika_3_team(),
			Setting::get_char_3(),
			Setting::get_special_3());
	}
	if (Input::MouseM.pressed)
	{
		OBJ_MGR->create_TestObj(SCENE_CAMERA->get_mouse_pos());
	}
	if (Input::MouseL.pressed)
	{
		if(Input::KeyControl.pressed)
		{
			if (OBJ_MGR->get_entity_from_id(UID_OBJ_MAP))
			{
				std::unique_ptr<Paint> p = std::make_unique<Paint>(Paint(SCENE_CAMERA->get_mouse_posP(), Setting::get_color_A()));
				MSG_DIS->dispatch_message(0, UID_UNKNOWN, UID_OBJ_MAP, msg::TYPE::MAP_PAINT, p.get());
			}
		}
		else
		{
			if (OBJ_MGR->get_entity_from_id(UID_OBJ_MAP))
			{
				std::unique_ptr<Paint> p = std::make_unique<Paint>(Paint(SCENE_CAMERA->get_mouse_posP(), Setting::get_color_B()));
				MSG_DIS->dispatch_message(0, UID_UNKNOWN, UID_OBJ_MAP, msg::TYPE::MAP_PAINT, p.get());
			}
		}


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