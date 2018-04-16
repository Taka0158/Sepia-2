#pragma once

//initializeとenter関数の用途が似すぎ	無駄
class Map :public Object
{
public:
	Map(ID _id) :Object(ID(_id)) {
		m_depth = -100;
		m_is_alive = true;
		m_p = Vec2(0.0, 0.0);
	};
	virtual ~Map() {};

	virtual void initialize()=0;
	virtual void finalize() =0;

	//Sceneの入った際に呼び出される
	virtual void enter() = 0;
	//メイン更新
	virtual void update() = 0;
	virtual void draw() = 0;
	//Sceneを出る際に呼び出される
	virtual void exit() = 0;

	virtual void debug_update() {};
	virtual void debug_draw() {};

	//単一オブジェクトよりidはマクロ指定
	virtual void set_id() {};
protected:

};

#include"MapSub\MapSimple.cpp"