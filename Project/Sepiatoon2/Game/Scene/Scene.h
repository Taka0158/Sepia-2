#pragma once

class SceneManager;
class CutScene;

class Scene
{
public:
	virtual void initialize() = 0;
	virtual void  finalize() = 0;

	//Sceneの入った際に呼び出される
	virtual void enter() = 0;
	//メイン更新
	virtual void update() = 0;
	virtual void draw() = 0;
	//Sceneを出る際に呼び出される
	virtual void exit() = 0;

	virtual void debug_update() = 0;
	virtual void debug_draw() = 0;

	//使用するStateでオーバーライド
	virtual void set_cut_scene(CutScene*) {};

	virtual void delete_cut_scene() 
	{
		if (m_cut_scene==nullptr)
		{

		}
		else
		{
			delete m_cut_scene;
			m_cut_scene = nullptr;
		}
	};

	virtual ~Scene() {};

	String get_scene_name() { return scene_name; };
	UIManager* get_ui() { return m_ui; };
protected:
	String scene_name;
	
	//シーンごとに別のUIにすべき？
	//規模が小さいので単一のUIで済ます
	//UIが存在しないSceneは　nullptr
	//		  する			 UIManager
	UIManager* m_ui = nullptr;

	CutScene* m_cut_scene = nullptr;
};

#include"CutScene\CutScene.cpp"