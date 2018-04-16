#pragma once

#include"Object.h"

class Map;

enum class MapType {
	SIMPLE
};

// GameMain
class ObjectManager : public Singleton<ObjectManager>,public Entity,public ManagerEntity
{
	friend class Singleton<ObjectManager>;
	ObjectManager();
	~ObjectManager();
public:

	void update();
	void debug_update();
	void draw();
	void debug_draw();

	void initialize();
	void finalize();

	//Create関数
	//テスト用
	void create_TestObj(Vec2 _p);

	//メッセージの受け取り関数
	bool handle_message(const Telegram& _msg)override;
	//メッセージの仕分けを行う関数
	//ここでメッセージに対応する処理を呼び出す
	bool on_message(const Telegram& _msg);

	//管理オブジェクトのIDによる探索
	Entity* get_entity_from_id(ID _id)override;

	//--------MAP関数-----
	void set_map(MapType);
	void destroy_map();
	//使う予定はない
	//連続バトル的なモードがあれば使用する？
	//Mapサブクラスから呼び出す
	void change_map(Map*);
private:

	//Objectが死んでいたら削除する
	void check_alive();
	
	//登録済みobjectのis_aliveをfalseにする
	void destroy_all_object();

	//各クラスのidをリセットする
	void reset_object_id();

	//描画順序付を行う
	void regist_draw_object(Object*);

	//描画順序付けを解除する
	void reset_draw_object(Object*);

	//create関数でobjectのインスタンスを作る場合
	//この関数に渡す
	void regist_object(Object*);


private:
	//オブジェクトのインスタンス（のポインタ）を格納する
	std::vector<Object*> m_objects;

	//<そのObjectのdepth	,	そのObjectのポインタ>
	typedef std::pair<int, Object*> Drawer;

	//object.m_depth基準で並び替える
	std::set<Drawer> m_objects_drawer;

	//mapインスタンス
	Map* m_map = nullptr;

};						 

ObjectManager* Singleton<ObjectManager>::instance = nullptr;
