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

	void update_sub();

	void debug_draw();
	bool handle_message(const Telegram& _msg)override;

	//Object�̍��W���J�����̒��S�ɂ���
	void set_center(Object*,bool);
	//�J�������S�������ɂ��킹��
	void set_center(Vec2,bool);



	Vec2 get_center_pos()const { return m_pos; };

	//�J�����ړ��ɉ������}�E�X�ʒu��Ԃ�
	//�������AScale 1�@�ȊO�̏ꍇ�@����ɋ@�\���Ȃ�
	Vec2 get_mouse_pos()
	{
		Vec2 temp = Vec2(SCENE_CAMERA->getCameraArea().pos);
		return (Mouse::PosF() + temp)*(1.0/m_scale);
	}
	Point get_mouse_posP()
	{
		Point temp = Vec2_to_Point(SCENE_CAMERA->getCameraArea().pos);
		return Mouse::Pos() + temp;
	}
private:
	//�X�P�[����ݒ肷��
	void set_scale();
	//��ʑ̃��X�g�ɓo�^����
	void regist_subject(MovingObject*);

	//��ʑ̃��X�g����Ȃ�
	void reset_subject(MovingObject*);

	//�J������h�炷
	void shake_screen(Vec2 _vec);
private:
	bool on_message(const Telegram&);

	//��ʑ�
	std::list<MovingObject*> m_subjects;

	//�h�炷���̕␳�l
	Vec2 m_shake_direction = Vec2(0.0, 0.0);

	//���Ƃɖ߂鑬���W��
	double m_friction = 0.02;

};

SceneCamera* Singleton<SceneCamera>::instance = nullptr;


