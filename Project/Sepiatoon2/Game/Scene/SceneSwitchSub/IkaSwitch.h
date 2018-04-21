#pragma once

class IkaSwitch :public SceneSwitch
{
public:
	IkaSwitch();
	~IkaSwitch();

	void update_sub()override;
	void draw()override;
private:
	//alpha�l
	int m_a;

	//��]�p�x
	double m_angle;

	//�g��䗦
	double m_scale;

	Texture m_ika;

};