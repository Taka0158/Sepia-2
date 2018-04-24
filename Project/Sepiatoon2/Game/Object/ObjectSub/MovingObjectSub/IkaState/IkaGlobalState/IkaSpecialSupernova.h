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

private:

	//SPECIAL状態の継続時間
	static double m_duration;
};

double IkaSpecialSupernova::m_duration = 3.0;