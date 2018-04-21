#pragma once

class IkaSwitch :public SceneSwitch
{
public:
	IkaSwitch();
	~IkaSwitch();

	void update_sub()override;
	void draw()override;
private:
	//alpha’l
	int m_a;

	//‰ñ“]Šp“x
	double m_angle;

	//Šg‘å”ä—¦
	double m_scale;

	Texture m_ika;

};