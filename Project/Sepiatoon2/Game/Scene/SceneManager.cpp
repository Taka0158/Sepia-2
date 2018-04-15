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

void SceneManager::change_scene(Scene* _scene)
{
	if (m_current_scene)
	{
		m_current_scene->exit();

		m_current_scene.reset(_scene);

		m_current_scene->enter();
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