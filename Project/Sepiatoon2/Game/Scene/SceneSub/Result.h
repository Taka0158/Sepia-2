#pragma once

class Result :public Scene
{
public:
	Result();
	~Result();

	void initialize();
	void finalize();

	virtual void enter();
	virtual void update();
	virtual void draw();
	void debug_update();
	void debug_draw();
	virtual void exit();
private:

};
