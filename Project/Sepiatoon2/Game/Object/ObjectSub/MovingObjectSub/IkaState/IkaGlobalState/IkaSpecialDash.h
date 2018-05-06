#pragma once


class IkaSpecialDash :public IkaState
{
public:
	IkaSpecialDash();
	~IkaSpecialDash();

	void input(Ika* _owner)override;
	void enter(Ika* _owner)override;
	void update(Ika* _owner)override;
	void draw(Ika* _owner)override;
	void exit(Ika* _owner)override;

	//localstate���g�p���邽��
	IkaStateType get_state_type()override;

	bool on_collide(Ika* _owner, CollidableObject* _obj);
private:
	//SPECIAL��Ԃ̌p������
	static int m_duration;

	int m_timer = 0;

	int m_tex_index = 0;
	bool m_is_tex_loop = true;

	Ika* m_owner = nullptr;

	//�Q�[�����p�����[�^
	double m_max_speed;

};

int IkaSpecialDash::m_duration = 420;