#pragma once


class IkaSpecialSupernova :public IkaState
{
public:
	IkaSpecialSupernova();
	~IkaSpecialSupernova();

	void state(Ika* _owner)override;
	void enter(Ika* _owner)override;
	void update(Ika* _owner)override;
	void draw(Ika* _owner)override;
	void exit(Ika* _owner)override;

	void fire(Ika*_owner);

private:
	int m_timer = 0;
	Color m_color;

	//���ߏ�ԗp
	int m_tex_ready_index = 0;

	int m_tex_index = 0;

	//���ߏ�Ԃ̌p���t���[��
	static int m_ready_duration;

	//���o���SPECIAL�p������
	static int m_duration;

	//�摜�̃X�P�[��
	static double m_scale;

	//inkball�ˏo�x�N�g��
	Vec2 m_fire_dir = Vec2(1.0, 0.0);

	//inkball�ˏo�Ԋu
	static int m_fire_interval;
	//inkball�ˏo�p�x
	double m_angle=0.0;

	//�ˏo����
	double m_length=1.0;


};

int IkaSpecialSupernova::m_ready_duration = 120;
int IkaSpecialSupernova::m_duration = 90;
int IkaSpecialSupernova::m_fire_interval = 2;
double IkaSpecialSupernova::m_scale = 2.0;
