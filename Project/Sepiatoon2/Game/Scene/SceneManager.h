#pragma once

#include"../Camera/SceneCamera.cpp"

#include"Scene.h"
//シーン切り替えクラスSceneSwitchの状態を定義
enum class SwitchType {
	FIRST,
	SWITCH,
	SECOND,
	END
};

#include"SceneSwitch.h"

namespace mine {

	class SceneManager :public Singleton<SceneManager>
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
	public:
		void debug_update();
		void debug_draw();
	private:
		std::unique_ptr<Scene> m_current_scene = nullptr;
		std::unique_ptr<Scene> m_next_scene = nullptr;
		std::unique_ptr<SceneSwitch> m_current_scene_switch = nullptr;
	};
}
#include"SceneSub\TestWorld.cpp"
#include"SceneSub\Title.cpp"


/*
Scene 純粋仮想関数

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