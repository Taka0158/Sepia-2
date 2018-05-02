#pragma once

class SelectChar :public SelectScene
{
public:
	SelectChar();
	~SelectChar();

	void initialize();
	void finalize();

	void enter();
	void update();
	void draw();
	void debug_update();
	void debug_draw();
	void exit();


	Texture* get_tex(int _index)override;

private:
	void object_describe()override;

};

int SelectChar::m_ready_durtion = 90;