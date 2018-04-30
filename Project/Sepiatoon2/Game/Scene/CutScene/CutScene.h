#pragma once

class Scene;
//必要なStateのみ持てばいい
class CutScene
{
public:
	CutScene(int32 _start,int32 _duration)
	{
		m_start_ms = _start;
		m_end_ms = _duration + _start;
	}
	virtual ~CutScene() {};

	virtual void enter(Scene*) = 0;
	virtual bool update(Scene*);
	virtual void update_sub(Scene*) {};
	
	virtual void draw(Scene*);
	virtual void draw_sub(Scene*) {};
	virtual void exit(Scene*) = 0;

protected:
	int32 m_start_ms;
	int32 m_end_ms;

	//開始時間と終了時間の間の現在時間における比率
	double m_ratio;

};

#include"CutSceneSub\IkaCutin.cpp"