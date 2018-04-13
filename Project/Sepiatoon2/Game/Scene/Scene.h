#pragma once

class SceneManager;

class Scene
{
public:
	virtual void initialize() = 0;
	virtual void  finalize() = 0;

	//�X�e�[�g�ɓ��������ɌĂяo�����
	virtual void enter() = 0;

	//���C���X�V
	virtual void update() = 0;
	virtual void debug_update() = 0;
	virtual void draw() = 0;
	virtual void debug_draw() = 0;

	//�X�e�[�g���o�����ɌĂяo�����
	virtual void exit() = 0;

	virtual ~Scene() {};

	String get_scene_name() { return scene_name; };
protected:
	String scene_name;
};