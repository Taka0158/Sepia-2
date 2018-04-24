#pragma once


class IkaSpecialDash :public IkaState
{
public:
	IkaSpecialDash();
	~IkaSpecialDash();

	void state(Ika* _owner)override;
	void enter(Ika* _owner)override;
	void update(Ika* _owner)override;
	void draw(Ika* _owner)override;
	void exit(Ika* _owner)override;

private:

	//SPECIALó‘Ô‚ÌŒp‘±ŠÔ
	static double m_duration;
};

double IkaSpecialDash::m_duration = 3.0;