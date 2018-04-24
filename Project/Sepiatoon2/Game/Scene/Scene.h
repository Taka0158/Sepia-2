#pragma once

class SceneManager;
class CutScene;

class Scene
{
public:
	virtual void initialize() = 0;
	virtual void  finalize() = 0;

	//Scene�̓������ۂɌĂяo�����
	virtual void enter() = 0;
	//���C���X�V
	virtual void update() = 0;
	virtual void draw() = 0;
	//Scene���o��ۂɌĂяo�����
	virtual void exit() = 0;

	virtual void debug_update() = 0;
	virtual void debug_draw() = 0;

	//�g�p����State�ŃI�[�o�[���C�h
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
	
	//�V�[�����Ƃɕʂ�UI�ɂ��ׂ��H
	//�K�͂��������̂ŒP���UI�ōς܂�
	//UI�����݂��Ȃ�Scene�́@nullptr
	//		  ����			 UIManager
	UIManager* m_ui = nullptr;

	CutScene* m_cut_scene = nullptr;
};

#include"CutScene\CutScene.cpp"