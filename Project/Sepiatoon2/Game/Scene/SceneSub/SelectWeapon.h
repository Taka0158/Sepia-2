#pragma once

class SelectWeapon :public SelectScene
{
public:
	SelectWeapon();
	~SelectWeapon();
	
	void initialize();
	void finalize();
	
	virtual void enter();
	virtual void update();
	virtual void draw();
	void debug_update();
	void debug_draw();
	virtual void exit();
private:
	void draw_object()override;

	void object_describe()override;
	
	void get_info(std::vector<String>& _container,int _index)override;

	void decide_p1()override;
	void decide_p2()override;

	Texture* get_tex(int _index)override { return nullptr; };
	Texture* get_tex(int _index,int& _tex_index);

	//ƒXƒyƒVƒƒƒ‹‚Ì‰æ‘œindex
	int m_tex_index_p1;
	int m_tex_index_p2;

};