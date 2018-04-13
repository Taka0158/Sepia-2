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
	}
}

void SceneManager::draw()
{
	if (m_current_scene)
	{
		m_current_scene->draw();
		m_current_scene->debug_draw();
	}

	debug();
}

void SceneManager::debug()
{
	if (m_current_scene)
	{
		Println(L"CurrentScene : " + m_current_scene->get_scene_name());
	}
	else
	{

	}
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