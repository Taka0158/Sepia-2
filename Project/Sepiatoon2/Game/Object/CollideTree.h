#pragma once

class CollideTree :public Singleton<CollideTree>, public Entity
{
	friend class Singleton<CollideTree>;
	CollideTree();
	virtual ~CollideTree();
public:

	void initialize();
	void finalize();

	//木に登録
	void register_object(CollidableObject* _obj);

	//登録オブジェクトから離脱届けを受け取る
	void remove_object(CollidableObject*);

	//衝突判定を行う
	void collide();

	void debug_draw();

	bool handle_message(const Telegram& _msg)override;
	bool on_message(const Telegram& _msg);
private:
	//デバグ表示用
	void debug_draw_collide(CollidableObject*, CollidableObject*);
	//引数と同じ添字（空間）内で衝突判定を行う 返り値はpushした数
	int collide_same_space(int _index, std::stack<CollidableObject*>& _stk);
	//子空間との衝突判定を行う
	void collide_sub(int _parent_index, std::stack<CollidableObject*>&,int);
	//stackの中の衝突オブジェクトと衝突判定を行う
	void collide_stacklist(int _index, std::stack<CollidableObject*>& _stk);

	//登録オブジェクトの数
	int m_count[COLLIDE_MAX_INDEX_SIZE] = {0};

	//4分木配列
	//中身はObject*の双方向リスト構造
	std::array<CollidableObject*, COLLIDE_MAX_INDEX_SIZE> m_collidable_objects;

	//最後尾のCollidableObjectを格納
	std::array<CollidableObject*,COLLIDE_MAX_INDEX_SIZE> m_list_last_objects;


};

CollideTree* Singleton<CollideTree>::instance = nullptr;