#pragma once

//Special�̌Ăяo���̓��b�Z�[�W���M�ōs��

class IkaSpecialTyphoon :public IkaState
{
public:
	IkaSpecialTyphoon();
	~IkaSpecialTyphoon();

	void state(Ika* _owner)override;
	void input(Ika* _owner)override;
	void enter(Ika* _owner)override;
	void update(Ika* _owner)override;
	void draw(Ika* _owner)override;
	void exit(Ika* _owner)override;

	//localstate���g�p���邽��
	IkaStateType get_state_type()override;

	bool on_collide(Ika* _owner, CollidableObject* _obj);
private:
	int m_timer = 0;

	int m_tex_index = 0;
	bool m_is_tex_loop = true;

	Ika* m_owner=nullptr;

	//SPECIAL��Ԃ̌p������
	static int m_duration;

	//�Q�[�����p�����[�^
	double m_paint_scale;
	double m_mask_radius;
	double m_draw_scale;
};

int IkaSpecialTyphoon::m_duration = 420;