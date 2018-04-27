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

	//ため状態用
	int m_tex_ready_index = 0;

	int m_tex_index = 0;

	//溜め状態の継続フレーム
	static int m_ready_duration;

	//放出後のSPECIAL継続時間
	static int m_duration;

	//画像のスケール
	static double m_scale;

	//inkball射出ベクトル
	Vec2 m_fire_dir = Vec2(1.0, 0.0);

	//inkball射出間隔
	static int m_fire_interval;
	//inkball射出角度
	double m_angle=0.0;

	//射出距離
	double m_length=1.0;


};

int IkaSpecialSupernova::m_ready_duration = 120;
int IkaSpecialSupernova::m_duration = 90;
int IkaSpecialSupernova::m_fire_interval = 2;
double IkaSpecialSupernova::m_scale = 2.0;
