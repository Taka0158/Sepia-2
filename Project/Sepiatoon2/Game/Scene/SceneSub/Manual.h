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
	//説明画像を描画する
	void draw_manual();
	//待ち時間
	static int m_wait_time;
	
	//文字のアルファ値
	int m_a;
	
};

int Manual::m_wait_time = 90;