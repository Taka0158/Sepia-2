#pragma once

//Specialの呼び出しはメッセージ送信で行う

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

	//localstateを使用するため
	IkaStateType get_state_type()override;

	bool on_collide(Ika* _owner, CollidableObject* _obj);
private:
	int m_timer = 0;

	int m_tex_index = 0;
	bool m_is_tex_loop = true;

	Ika* m_owner=nullptr;

	//SPECIAL状態の継続時間
	static int m_duration;

	//ゲーム内パラメータ
	double m_paint_scale;
	double m_mask_radius;
	double m_draw_scale;
};

int IkaSpecialTyphoon::m_duration = 420;