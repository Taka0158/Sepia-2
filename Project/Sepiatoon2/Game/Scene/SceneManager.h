#pragma once

#include"Scene.h"

class SceneManager :public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;
	SceneManager();
public:
	~SceneManager();

	void update();
	void draw();
	void initialize();
	void finalize();

	void change_scene(Scene*);
public:
	void debug();
private:
	std::unique_ptr<Scene> m_current_scene = nullptr;
};

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