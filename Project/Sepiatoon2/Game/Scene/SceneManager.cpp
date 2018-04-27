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
		m_current_scene.reset(new Title());
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
		
		if (m_current_scene->get_ui() != nullptr)
		{
			m_current_scene->get_ui()->update();
			m_current_scene->get_ui()->debug_update();
		}
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
		m_current_scene->debug_draw();

		if (m_current_scene->get_ui() != nullptr)
		{
			m_current_scene->get_ui()->draw();
			m_current_scene->get_ui()->debug_draw();
		}
	}

	if (m_current_scene_switch)
	{
		m_current_scene_switch->draw();
		m_current_scene_switch->debug_draw();
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
	SCENE_CAMERA->debug_draw();
}

void mine::SceneManager::change_scene(Scene* _scene,SceneSwitch* _switch)
{
	if (m_current_scene)
	{
		if (!m_next_scene)
		{
			m_next_scene.reset(_scene);

			m_current_scene_switch.reset(_switch);
		}
	}
	else
	{
		ASSERT("シーンが存在しないのに mine::SceneManager::change_scene が呼ばれました");
	}
}
void mine::SceneManager::change_scene()
{
	if (m_current_scene)
	{
		if ( m_next_scene && m_current_scene_switch->get_state() == SwitchType::SWITCH)
		{
			m_current_scene->exit();

			m_current_scene=std::move(m_next_scene);

			m_next_scene.release();

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

	switch (_msg.msg)
	{
	case msg::TYPE::SET_CUTIN:
		Ika* sender = (Ika*)_msg.extraInfo;
		//CutInTypeは選べるようにしたいTODO
		if (m_current_scene)m_current_scene->set_cut_scene(CutInType::IKA_CUTIN, sender->get_color());
		ret = true;
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