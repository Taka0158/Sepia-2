#pragma once

//衝突可能オブジェクト
class CollidableObject :public Entity
{
public:
	//番兵用コンストラクタ
	CollidableObject() :Entity(UID_UNKNOWN) {};

	CollidableObject(ID _id) :Entity(ID(UID_MGR_OBJ) | _id){};

	virtual ~CollidableObject() {};	  

	//長方形のマスクを使う場合はoverride
	virtual void mask_update() { m_mask.setPos(m_pos).setSize(m_mask_radius); };

	virtual bool handle_message(const Telegram& msg) { return false; };


	Vec2 get_p()const { return m_pos; };
	Circle& get_mask() { return m_mask; };
	double get_mask_radius() { return m_mask_radius; };
	double set_mask_radius(double _s) { m_mask_radius=_s; };
	double get_height() { return m_height; }
	void set_height(double _s) { m_height = _s; }
	double get_mask_height() { return m_mask_height; };

	//衝突判定の受け取りを行う
	virtual bool handle_collide(CollidableObject*  _obj) { return false; };


	//衝突判定4分木から登録を外す
	void remove_from_tree();

	//モートン番号と所属空間レベルを更新する
	void update_morton_and_level();

	//モートン番号とlevelの初期化を行う
	void init_morton_and_level();

	//m_posをルート空間内に収める
	void restrain_area();

	int get_morton_number() { return m_morton_number; }
	int get_level() { return m_level; }
	int get_ary_index() { return m_ary_index; }
	CollidableObject* get_previous_object() { return m_previous_object; }
	CollidableObject* get_next_object() { return m_next_object; }
	void set_previous_object(CollidableObject* _obj) { m_previous_object = _obj; }
	void set_next_object(CollidableObject* _obj) { m_next_object= _obj; }



protected:
	//メッセージ処理を行う関数
	virtual bool on_message(const Telegram&) { return false; };

	//衝突処理を行う
	virtual bool on_collide(CollidableObject* _obj) { return false; };

	//自身の中心座標
	Vec2 m_pos;

	//地面からの高さ
	double m_height = 0.0;

	//コリジョンマスク
	Circle m_mask = Circle(0, 0, 0);

	//コリジョンマスクの大きさ
	double m_mask_radius = 1.0;

	//コリジョンマスクの高さ
	double m_mask_height = 2.0;

	//同じ木配列に属している次のオブジェクトを指し示す
	CollidableObject* m_next_object = nullptr;
	//前のオブジェクトを指す
	CollidableObject* m_previous_object = nullptr;

	//所属空間のモートン番号
	int m_morton_number=0;

	//所属空間のレベル
	int m_level=0;

	//木構造配列にいれるindex
	int m_ary_index=0;


};

void CollidableObject::init_morton_and_level()
{
	Point p = collide::get_bounding_box(m_mask).second;
	//ルート画面外にはイカないようにする
	m_morton_number = collide::get_morton_order_from_index(p);

	m_level = collide::get_level_from_mask(m_mask);

	m_ary_index = collide::get_index_form_morton_num_and_level(m_morton_number, m_level);

}


void CollidableObject::update_morton_and_level()
{

	Point p = Vec2_to_Point(m_pos);
	//ルート画面外にはイカないようにする
	int new_morton = collide::get_morton_order_from_index(p);

	if (m_morton_number == new_morton)return;

	m_morton_number = new_morton;

	m_level = collide::get_level_from_mask(m_mask);

	int new_ary_index = collide::get_index_form_morton_num_and_level(m_morton_number, m_level);

	//配列indexに変更があれば
	if (new_ary_index != m_ary_index)
	{
		//木の変更を行う
		remove_from_tree();
		m_ary_index = new_ary_index;
		MSG_DIS->dispatch_message(0.0, UID_UNKNOWN, UID_COLLIDE_TREE, msg::TYPE::REGISTER_TO_COLLIDE_TREE, this, false);
	}
	else
	{

	}

}

void CollidableObject::remove_from_tree()
{
	//次のオブジェクトがいなければ
	if (m_next_object == nullptr)
	{
		//木に最後尾が離脱することを伝える
		MSG_DIS->dispatch_message(0.0, UID_UNKNOWN, UID_COLLIDE_TREE, msg::TYPE::REMOVE_FROM_COLLIDE_TREE, this,false);
		m_previous_object->set_next_object(nullptr);
		m_previous_object = nullptr;

	}
	else
	{
		//前後のつけかえ
		m_previous_object->set_next_object(m_next_object);
		m_next_object->set_previous_object(m_previous_object);
		m_next_object = nullptr;
		m_previous_object = nullptr;
	}
}

void CollidableObject::restrain_area()
{
	m_pos = clamp(m_pos, Vec2(0.1, 0.1), Vec2(COLLIDE_SPACE_WIDTH - 1, COLLIDE_SPACE_HEIGHT - 1));
}