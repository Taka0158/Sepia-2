#pragma once


class FadeInOut :public SceneSwitch
{
public:
	FadeInOut();
	~FadeInOut();

	void update_sub()override;
	void draw()override;
private:
	//alpha’l
	int m_a;
	Rect m_r;

};