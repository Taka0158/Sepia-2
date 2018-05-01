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
	DEBUG->regist(DebugText(3.0, L"------------------TESTWORLDデストラクタ----------------"));
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
	delete_cut_scene();
}

void TestWorld::enter()
{

}

void TestWorld::exit()
{

}

void TestWorld::update()
{
	if (m_cut_scene)
	{
		if (m_cut_scene->update(this)==false)
		{
			delete_cut_scene();
		}
	}
	else 
	{
		SCENE_CAMERA->update_sub();
		OBJ_MGR->update();
		//EFFECT_MGR->update();
		OBJ_MGR->debug_update();
	}
}

void TestWorld::draw()
{
	//カメラの影響下
	SCENE_CAMERA->update();
	{
		const auto t1 = SCENE_CAMERA->createTransformer();

		OBJ_MGR->draw();
		//EFFECT_MGR->draw();
		OBJ_MGR->debug_draw();
	}

	if (m_cut_scene)m_cut_scene->draw(this);

}

void TestWorld::debug_update()
{

	if (Input::KeyZ.clicked)
	{
		OBJ_MGR->create_Ika(1, Vec2(160, 160));
	}
	if (Input::KeyX.clicked)
	{
		OBJ_MGR->create_Ika(2, Vec2(1920-160,1080 -160));
	}
	if (Input::KeyC.clicked)
	{
		OBJ_MGR->create_Ika(3, Vec2(160,1080- 160));
	}
	if (Input::KeyV.clicked)
	{
		OBJ_MGR->create_Ika(4, Vec2(1920-160, 160));
	}
	if (Input::MouseM.clicked)
	{
		OBJ_MGR->create_Tire(SCENE_CAMERA->get_mouse_pos());
	}
	if (Input::KeyT.pressed)
	{
		OBJ_MGR->create_Rumba(SCENE_CAMERA->get_mouse_pos(), Setting::get_color(TeamType::TEAM_A));
	}
	if (Input::KeyG.pressed)
	{
		OBJ_MGR->create_Rumba(SCENE_CAMERA->get_mouse_pos(), Setting::get_color(TeamType::TEAM_B));
	}

	if (Input::KeyU.pressed)
	{
		REP(i, 10)
		{
			InkballParm ibp = InkballParm(SCENE_CAMERA->get_mouse_pos(), 10.0, RandomVec2(1.0), 5.0, Setting::get_color(TeamType::TEAM_A));
			MSG_DIS->dispatch_message(0.0, UID_UNKNOWN, UID_MGR_OBJ, msg::TYPE::CREATE_INK_BALL, &ibp, false);

		}
	}
	if (Input::KeyJ.pressed)
	{
		REP(i, 10)
		{
			InkballParm ibp = InkballParm(SCENE_CAMERA->get_mouse_pos(), 10.0, RandomVec2(1.0), 5.0, Setting::get_color(TeamType::TEAM_B));
			MSG_DIS->dispatch_message(0.0, UID_UNKNOWN, UID_MGR_OBJ, msg::TYPE::CREATE_INK_BALL, &ibp, false);

		}
	}

	if (Input::MouseL.pressed)
	{
		if(Input::KeyControl.pressed)
		{
			if (OBJ_MGR->get_entity_from_id(UID_OBJ_MAP))
			{
				std::unique_ptr<Paint> p = std::make_unique<Paint>(Paint(SCENE_CAMERA->get_mouse_posP(), Setting::get_color(TeamType::TEAM_A)));
				MSG_DIS->dispatch_message(0, UID_UNKNOWN, UID_OBJ_MAP, msg::TYPE::MAP_PAINT, p.get());
			}
		}
		else
		{
			if (OBJ_MGR->get_entity_from_id(UID_OBJ_MAP))
			{
				std::unique_ptr<Paint> p = std::make_unique<Paint>(Paint(SCENE_CAMERA->get_mouse_posP(), Setting::get_color(TeamType::TEAM_B)));
				MSG_DIS->dispatch_message(0, UID_UNKNOWN, UID_OBJ_MAP, msg::TYPE::MAP_PAINT, p.get());
			}
		}


	}
	if (Input::KeyF1.clicked)
	{
		initialize();
		DEBUG->regist(DebugText(5, L"初期化"));
	}
	if (Input::KeyF2.clicked)
	{
		OBJ_MGR->set_map(MapType::SIMPLE);
	}
	if (Input::KeyF3.clicked)
	{
		OBJ_MGR->destroy_map();
	}

	if (Input::KeyF7.clicked)
	{
		//set_cut_scene(new IkaCutin(Setting::get_color(Setting::get_ika_1_team())));
	}

}

void TestWorld::debug_draw()
{

}

void TestWorld::set_cut_scene(CutInType _type,Color _color)
{
	if (m_cut_scene != nullptr)return;
	switch (_type)
	{
	case CutInType::IKA_CUTIN:
		m_cut_scene.reset(new IkaCutin(_color));
		break;
	}
}