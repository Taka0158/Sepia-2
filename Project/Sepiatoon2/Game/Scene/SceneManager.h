#pragma once

#include"../Camera/SceneCamera.cpp"

#include"Scene.h"


#include"SceneSwitch.h"

namespace mine {

	class SceneManager :public Singleton<SceneManager>,public Entity
	{
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
	public:

		void update();
		void draw();
		void initialize();
		void finalize();

		void change_scene(Scene*, SceneSwitch* = new IkaIkaSwitch());
		void change_scene();

		bool handle_message(const Telegram& _msg)override;
														 
	public:
		void debug_update();
		void debug_draw();
		Scene* get_current_scene() { return m_current_scene.get(); }
	private:
		bool on_message(const Telegram& _msg);
		std::unique_ptr<Scene> m_current_scene = nullptr;
		std::unique_ptr<Scene> m_next_scene = nullptr;
		std::unique_ptr<SceneSwitch> m_current_scene_switch = nullptr;
	};
}
#include"SceneSub\TestWorld.cpp"
#include"SceneSub\Title.cpp"


/*
Scene èÉêàâºëzä÷êî

class T :public Scene
{
public:
	T();
	~T();

	void initialize();
	void finalize();

	virtual void enter();
	virtual void update();
	virtual void draw();
	void debug_update();
	void debug_draw();
	virtual void exit();
private:

};

---------------------------

*/