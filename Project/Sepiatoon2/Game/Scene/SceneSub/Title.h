#pragma once

class Title :public Scene
{
public:
	Title();
	~Title();

	void initialize();
	void finalize();

	void enter();
	void update();

	void debug_update();
	void debug_draw();

	void draw();
	void exit();

private:
};

