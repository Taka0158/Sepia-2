#pragma once

class IkaIkaSwitch :public SceneSwitch
{
public:
	IkaIkaSwitch();
	~IkaIkaSwitch();

	void update_sub()override;
	void draw()override;
private:
	int m_ika_num;

	Rect m_rect[8];
};