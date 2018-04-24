#pragma once


class TestWorld :public Scene
{
public:
	TestWorld();
	~TestWorld();

	void initialize();
	void finalize();

	virtual void enter();
	virtual void update();
	virtual void draw();
	void debug_update();
	void debug_draw();
	virtual void exit();

	void set_cut_scene(CutScene*)override;
private:

};