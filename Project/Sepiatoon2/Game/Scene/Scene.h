#pragma once

class SceneManager;

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
};