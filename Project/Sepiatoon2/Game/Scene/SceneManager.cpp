#include"SceneManager.h"


mine::SceneManager::SceneManager():Entity(UID_MGR_SCENE)
{
	initialize();
}

mine::SceneManager::~SceneManager()
{
	finalize();
}

void mine::SceneManager::initialize()
{
	finalize();
	if (!m_current_scene)
	{
		m_current_scene.reset(new Start());

		m_current_scene->enter();
	}
	else
	{
		ASSERT("既にシーンが存在し、不正なシーン遷移です");
	}
}

void mine::SceneManager::finalize()
{
	if (!m_current_scene)
	{
		m_current_scene.reset();
	}
	if (!m_current_scene_switch)
	{
		m_current_scene_switch.reset();
	}
}

void mine::SceneManager::update()
{
	if (m_current_scene)
	{
		m_current_scene->update();
		m_current_scene->debug_update();
		
	}

	if (m_current_scene_switch)
	{
		SwitchType type = m_current_scene_switch->update();
		if (type == SwitchType::SWITCH)change_scene();
		else if (type == SwitchType::END)
		{
			m_current_scene_switch.reset();
		}
	}

	
}

void mine::SceneManager::draw()
{

	if (m_current_scene)
	{
		m_current_scene->draw();

	}

	if (m_current_scene_switch)
	{
		m_current_scene_switch->draw();
	}

}

void mine::SceneManager::debug_update()
{
	if (m_current_scene)
	{

	}

	if (Input::KeyLControl.pressed && Input::Key0.clicked)
	{
		if (dynamic_cast<TestWorld*>(m_current_scene.get()))
		{
			change_scene(new Title(),new IkaSwitch());
		}
		else
		{
			change_scene(new TestWorld());
		}
	}
}


void mine::SceneManager::debug_draw()
{
	if (m_current_scene)
	{
		Println(L"CurrentScene : " + m_current_scene->get_scene_name());
	}
	else
	{

	}

	if (m_current_scene)
	{
		m_current_scene->debug_draw();

	}

	if (m_current_scene_switch)
	{
		m_current_scene_switch->debug_draw();
	}

	SCENE_CAMERA->debug_draw();
}

void mine::SceneManager::change_scene(Scene* _scene,SceneSwitch* _switch)
{
	//現在のシーンが有効なら
	if (m_current_scene)
	{
		//次のシーンが存在しないならば
		if (!m_next_scene)
		{
			m_next_scene.reset(_scene);

			m_current_scene_switch.reset(_switch);
		}
		else
		{
			//既に次のシーンが準備されているならば
			delete _scene;
			delete _switch;
		}
	}
	else
	{

		ASSERT("シーンが存在しないのに mine::SceneManager::change_scene が呼ばれました");
	}
}
void mine::SceneManager::change_scene()
{
	//現在のシーンが有効なら
	if (m_current_scene)
	{
		//次のシーンが準備され
		//シーン遷移の状態がSWITCHならば
		if ( m_next_scene && m_current_scene_switch->get_state() == SwitchType::SWITCH)
		{
			m_current_scene->exit();

			Scene* next_scene = m_next_scene.get();

			m_next_scene.release();

			m_current_scene.reset(next_scene);

			m_current_scene->enter();
		}
	}
	else
	{
		ASSERT("シーンが存在しないのに mine::SceneManager::change_scene が呼ばれました");
	}
}

bool mine::SceneManager::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool mine::SceneManager::on_message(const Telegram& _msg)
{
	bool ret = false;

	if (_msg.msg == msg::TYPE::SET_CUTIN)
	{
		Ika* sender = (Ika*)_msg.extraInfo;
		//CutInTypeは選べるようにしたいTODO
		if (m_current_scene)m_current_scene->set_cut_scene(CutInType::IKA_CUTIN, sender->get_color());
		ret = true;
	}
	else if(_msg.msg == msg::TYPE::SCENE_MGR_SET_NEXT_SCENE)
	{
		SceneParam* next_scene = (SceneParam*)_msg.extraInfo;
		change_scene(get_new_scene_from_type((*next_scene).st), get_new_scene_switch_from_type((*next_scene).sst));
		ret = true;
	}
	return ret;
}

Scene* mine::SceneManager::get_new_scene_from_type(SceneType _type)
{
	typedef SceneType ST;
	Scene* ret = nullptr;

	switch (_type)
	{
	case ST::GAMEMAIN:
		ret = new GameMain();
		break;
	case ST::MANUAL:
		ret = new Manual();
		break;
	case ST::OPTION:
		ret = new Option();
		break;
	case ST::RESULT:
		ret = new Result();
		break;
	case ST::SELECTCHAR:
		ret = new SelectChar();
		break;
	case ST::SELECTMAP:
		ret = new SelectMap();
		break;
	case ST::SELECTPLAYMODE:
		ret = new SelectPlayMode();
		break;
	case ST::SELECTWEAPON:
		ret = new SelectWeapon();
		break;
	case ST::TESTWORLD:
		ret = new TestWorld();
		break;
	case ST::TITLE:
		ret = new Title();
		break;
	}

	return ret;
}

SceneSwitch* mine::SceneManager::get_new_scene_switch_from_type(SceneSwitchType _type)
{
	typedef SceneSwitchType SST;
	SceneSwitch* ret = nullptr;

	switch (_type)
	{
	case SST::FADEIN_FADEOUT:
		ret = new FadeInOut();
		break;
	case SST::IKA:
		ret = new IkaSwitch();
		break;
	case SST::IKAIKA:
		ret = new IkaIkaSwitch();
		break;
	}

	return ret;
}


mine::SceneManager* Singleton<mine::SceneManager>::instance = nullptr;

/*

T::T()
{
scene_name = L"T";
initialize();
}

T::~T()
{
finalize();
}

void T::initialize()
{

}

void T::finalize()
{

}

void T::enter()
{

}

void T::exit()
{

}

void T::update()
{

}

void T::draw()
{

}

void T::debug_update()
{

}

void T::debug_draw()
{

}

*/