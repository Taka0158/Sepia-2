#pragma once

class IkaDamaged :public IkaState
{
public:
	IkaDamaged();
	~IkaDamaged();

	void state(Ika* _owner)override;
	void enter(Ika* _owner)override;
	void update(Ika* _owner)override;
	void draw(Ika* _owner)override;
	void exit(Ika* _owner)override;

private:
	//–³“GŽžŠÔ(sec)
	static double m_invincible_time;
};

double IkaDamaged::m_invincible_time = 3.0;