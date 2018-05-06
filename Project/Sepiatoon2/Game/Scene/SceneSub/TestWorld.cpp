#include"TestWorld.h"

TestWorld::TestWorld()
{
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
	UI_MGR->initialize();
	SCENE_CAMERA->initialize();
}

void TestWorld::finalize()
{
	OBJ_MGR->finalize();
	SCENE_CAMERA->finalize();
	UI_MGR->finalize();
	MSG_DIS->destroy_all_message();
	delete_cut_scene();
}

void TestWorld::enter()
{
	init_background();
}

void TestWorld::exit()
{

}

void TestWorld::update()
{
	m_timer++;
	update_ika_pos();

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
		if(!Input::KeyP.pressed)OBJ_MGR->update();
		//EFFECT_MGR->update();
		UI_MGR->update();

	}
}

void TestWorld::draw()
{
	draw_background();

	//カメラの影響下
	SCENE_CAMERA->update();
	{
		const auto t1 = SCENE_CAMERA->createTransformer();

		OBJ_MGR->draw();
		//EFFECT_MGR->draw()
		OBJ_MGR->debug_draw();
		UI_MGR->draw();
		UI_MGR->debug_draw();
	}

	if (m_cut_scene)m_cut_scene->draw(this);

}

void TestWorld::debug_update()
{

	if (Input::KeyZ.clicked)
	{
		int index = 1;
		MSG_DIS->dispatch_message(0.0, ID(UID_MGR_SCENE), ID(ID_MAPGIMMCIK_RESPAWN_POINT), msg::TYPE::RESPAWN_IKA, &index);

	}
	if (Input::KeyX.clicked)
	{
		int index = 2;
		MSG_DIS->dispatch_message(0.0, ID(UID_MGR_SCENE), ID(ID_MAPGIMMCIK_RESPAWN_POINT), msg::TYPE::RESPAWN_IKA, &index);
	}
	if (Input::KeyC.clicked)
	{
		int index = 3;
		MSG_DIS->dispatch_message(0.0, ID(UID_MGR_SCENE), ID(ID_MAPGIMMCIK_RESPAWN_POINT), msg::TYPE::RESPAWN_IKA, &index);
	}
	if (Input::KeyV.clicked)
	{
		int index = 4;
		MSG_DIS->dispatch_message(0.0, ID(UID_MGR_SCENE), ID(ID_MAPGIMMCIK_RESPAWN_POINT), msg::TYPE::RESPAWN_IKA, &index);
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
	if (Input::KeyY.clicked)
	{
		OBJ_MGR->create_Wall(SCENE_CAMERA->get_mouse_pos());
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
	if (Input::KeyF6.clicked)
	{
		OBJ_MGR->set_map(MapType::SIMPLE_BIG);
	}
	if (Input::KeyF8.clicked)
	{
		OBJ_MGR->set_map(MapType::CLASSIC);
	}
	if (Input::KeyF3.clicked)
	{
		OBJ_MGR->destroy_map();
	}
	if (Input::KeyH.clicked)
	{
		MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_OBJ, msg::TYPE::ALL_WALL_PAINT);
	}

	if (Input::KeyF7.clicked)
	{
		//set_cut_scene(new IkaCutin(Setting::get_color(Setting::get_ika_1_team())));
	}

	if (Input::KeyR.clicked)
	{
		OBJ_MGR->create_Missile(SCENE_CAMERA->get_mouse_pos(), 50, Setting::get_color(TeamType::TEAM_B));
	}
	if (Input::KeyF.clicked)
	{
		OBJ_MGR->create_Missile(SCENE_CAMERA->get_mouse_pos(), 50, Setting::get_color(TeamType::TEAM_A));
	}
	if (Input::KeyE.clicked)
	{
		OBJ_MGR->create_Missile(SCENE_CAMERA->get_mouse_pos(), 50, Setting::get_color(TeamType::TEAM_A),MissileType::RAIN);
	}
	if (Input::KeyB.clicked)
	{
		OBJ_MGR->create_IkaBalloon(SCENE_CAMERA->get_mouse_pos(), IkaBalloonType::ITEM);
	}
	if (Input::KeyN.clicked)
	{
		OBJ_MGR->create_IkaBalloon(SCENE_CAMERA->get_mouse_pos(), IkaBalloonType::ORB);
	}
	if (Input::KeyM.clicked)
	{
		if (Input::KeyLControl.pressed)
		{
			OrbParm op = OrbParm(SCENE_CAMERA->get_mouse_pos(), 10.0, RandomVec2(1.0),5, OrbType::NORMAL);
			MSG_DIS->dispatch_message(0.0, UID_UNKNOWN, UID_MGR_OBJ, msg::TYPE::CREATE_INK_BALL, &op, false);
		}
		else
		{
			OrbParm op = OrbParm(SCENE_CAMERA->get_mouse_pos(), 10.0, RandomVec2(1.0), 5, OrbType::SPECIAL);
			MSG_DIS->dispatch_message(0.0, UID_UNKNOWN, UID_MGR_OBJ, msg::TYPE::CREATE_INK_BALL, &op, false);
		}

	}

	OBJ_MGR->debug_update();
	UI_MGR->debug_update();
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