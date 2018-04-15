#include"SceneManager.h"


SceneManager::SceneManager()
{
	initialize();
}

SceneManager::~SceneManager()
{
	finalize();
}

void SceneManager::initialize()
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

void SceneManager::finalize()
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

void SceneManager::update()
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

void SceneManager::draw()
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

void SceneManager::debug_update()
{
	if (m_current_scene)
	{
	}

	if (Input::KeyLControl.pressed && Input::Key0.clicked)
	{
		if (dynamic_cast<TestWorld*>(m_current_scene.get()))
		{
			change_scene(new Title());
		}
		else
		{
			change_scene(new TestWorld());
		}
	}
}


void SceneManager::debug_draw()
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

void SceneManager::change_scene(Scene* _scene,SceneSwitch* _switch)
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
		ASSERT("シーンが存在しないのに SceneManager::change_scene が呼ばれました");
	}
}
void SceneManager::change_scene()
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
		ASSERT("シーンが存在しないのに SceneManager::change_scene が呼ばれました");
	}
}


SceneManager* Singleton<SceneManager>::instance = nullptr;

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