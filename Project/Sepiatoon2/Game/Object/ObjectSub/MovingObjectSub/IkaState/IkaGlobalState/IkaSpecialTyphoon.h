#pragma once

//Specialの呼び出しはメッセージ送信で行う

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

	//SPECIAL状態の継続時間
	static double m_duration;
};

double IkaSpecialTyphoon::m_duration = 3.0;