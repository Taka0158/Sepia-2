#pragma once

class Scene;
//�K�v��State�̂ݎ��Ă΂���
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

	//�J�n���ԂƏI�����Ԃ̊Ԃ̌��ݎ��Ԃɂ�����䗦
	double m_ratio;

};

#include"CutSceneSub\IkaCutin.cpp"