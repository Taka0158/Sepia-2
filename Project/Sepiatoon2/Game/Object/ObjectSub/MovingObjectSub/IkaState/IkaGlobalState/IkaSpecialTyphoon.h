#pragma once

//Special�̌Ăяo���̓��b�Z�[�W���M�ōs��

class IkaSpecialTyphoon :public IkaState
{
public:
	IkaSpecialTyphoon();
	~IkaSpecialTyphoon();

	void state(Ika* _owner)override;
	void enter(Ika* _owner)override;
	void update(Ika* _owner)override;
	void draw(Ika* _owner)override;
	void exit(Ika* _owner)override;

private:

	//SPECIAL��Ԃ̌p������
	static double m_duration;
};

double IkaSpecialTyphoon::m_duration = 3.0;