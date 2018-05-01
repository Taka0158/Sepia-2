#pragma once
class Object :public Entity
{
public:
	Object(ID _id) :Entity(ID(UID_MGR_OBJ) | _id) 
	{

	};
	virtual ~Object() {};

	virtual void initialize()=0;
	virtual void finalize()=0;
	virtual void update()=0;
	virtual void draw()=0;

	virtual void debug_update() {};
	virtual void debug_draw() {};
	virtual void mask_update() {};

	bool get_is_alive()const { return m_is_alive; };
	Vec2 get_p()const { return m_pos; };
	int get_depth()const { return m_depth; };
	int& get_depth_ref() { return m_depth; };
	void set_is_alive(bool _b) { m_is_alive = _b; };
	Circle& get_mask() { return m_mask; };
	double get_mask_radius() { return m_mask_radius; };
	double get_height() { return m_height; }
	void set_height(double _s) { m_height = _s; }
	double get_mask_height() { return m_mask_height; };

	//IDを設定する
	virtual void set_id() = 0;

	//IDを初期化する
	virtual void init_id() = 0;
	
	//衝突判定の受け取りを行う
	virtual bool handle_collide(Object*  _obj) { return false; };

	//高さ考慮の描画中心座標
	Vec2 get_pos_height() { return Vec2(m_pos.x, m_pos.y - m_height); }


protected:
	//メッセージ処理を行う関数
	virtual bool on_message(const Telegram&) { return false; };

	//衝突処理を行う
	virtual bool on_collide(Object* _obj) { return false; };

	//死んでいるか生きているか
	bool m_is_alive;

	//自身の中心座標
	Vec2 m_pos;

	//描画深度　大きいほど後に描画 地面は0
	int m_depth = 0;

	//地面からの高さ
	double m_height = 0.0;

	int m_init_depth = 0;

	//コリジョンマスク
	Circle m_mask = Circle(0, 0, 0);

	//コリジョンマスクの大きさ
	double m_mask_radius=1.0;

	//コリジョンマスクの高さ
	double m_mask_height = 2.0;

};


#include"ObjectSub\Map.cpp"
#include"ObjectSub\TestObj.cpp"
#include"ObjectSub\MovingObject.h"

//比較演算子のオーバーロード
//描画順序の定義
inline bool operator==(const Object& _o1, const Object& _o2)
{
	return (_o1.get_depth() == _o2.get_depth());
}
inline bool operator<(const Object& _o1, const Object& _o2)
{
	if (_o1 == _o2)
	{
		return false;
	}
	else
	{
		return (_o1.get_depth() < _o2.get_depth());
	}
}
