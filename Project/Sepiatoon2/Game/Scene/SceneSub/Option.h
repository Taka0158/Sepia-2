#pragma once

class Option :public Scene
{
public:
	Option();
	~Option();

	void initialize();
	void finalize();

	virtual void enter();
	virtual void update();
	virtual void draw();

	virtual void debug_update();
	virtual void debug_draw();

	virtual void exit();
private:

};