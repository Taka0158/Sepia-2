#pragma once

class Manual :public Scene
{
public:
	Manual();
	~Manual();

	void initialize();
	void finalize();

	virtual void enter();
	virtual void update();
	virtual void draw();
	void debug_update();
	void debug_draw();
	virtual void exit();
private:
	//�����摜��`�悷��
	void draw_manual();
	//�҂�����
	static int m_wait_time;
	
	//�����̃A���t�@�l
	int m_a;
	
};

int Manual::m_wait_time = 90;