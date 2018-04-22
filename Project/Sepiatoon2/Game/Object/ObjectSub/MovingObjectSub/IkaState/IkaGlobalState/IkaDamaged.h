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
	int timer = 0;

	static int m_invincible_time;
};

int IkaDamaged::m_invincible_time = 100;