#pragma once

//OBJ_MGR��EFFECT_MGR���J�����̉e�����󂯂�

class SceneCamera :public ham::Camera2D,public Singleton<SceneCamera>,public Entity
{
	friend class Singleton<SceneCamera>;
public:		
	SceneCamera();
	~SceneCamera();

	void initialize();
	void finalize();

	void debug_draw();
	bool handle_message(const Telegram& _msg)override;

	//Object�̍��W���J�����̒��S�ɂ���
	void set_center(Object*,bool);
	//�J�������S�������ɂ��킹��
	void set_center(Vec2,bool);

	//�J�����ړ��ɉ������}�E�X�ʒu��Ԃ�
	//�������AScale 1�@�ȊO�̏ꍇ�@����ɋ@�\���Ȃ�
	static Vec2 get_mouse_pos()
	{
		Vec2 temp = Vec2(SCENE_CAMERA->getCameraArea().pos);
		return Mouse::Pos() + temp;
	}
private:
	bool on_message(const Telegram&);
};

SceneCamera* Singleton<SceneCamera>::instance = nullptr;


