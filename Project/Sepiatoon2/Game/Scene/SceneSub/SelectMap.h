#pragma once

class SelectMap :public Scene
{
public:
SelectMap();
~SelectMap();

	void initialize();
	void finalize();
	
	virtual void enter();
	virtual void update();
	virtual void draw();
	void debug_update();
	void debug_draw();
	virtual void exit();
private:	
	Texture* get_tex(int _index);

	void map_describe();

};