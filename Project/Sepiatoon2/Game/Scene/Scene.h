#pragma once

class SceneManager;

class Scene
{
public:
	virtual void initialize() = 0;
	virtual void  finalize() = 0;

	//ステートに入った時に呼び出される
	virtual void enter() = 0;

	//メイン更新
	virtual void update() = 0;
	virtual void debug_update() = 0;
	virtual void draw() = 0;
	virtual void debug_draw() = 0;

	//ステートを出た時に呼び出される
	virtual void exit() = 0;

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
};