#pragma once

class GameMain :public Scene
{
public:
	GameMain();
	~GameMain();

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