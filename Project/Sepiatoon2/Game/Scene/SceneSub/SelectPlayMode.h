#pragma once

class SelectPlayMode :public Scene
{
public:
	SelectPlayMode();
	~SelectPlayMode();

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