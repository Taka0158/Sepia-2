#pragma once

#include"Object.h"

class Map;

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


	//-----------------------------------------------Create関数--------------------------------------------------------------------------
	//テスト用
	//void create_TestObj(Vec2 _p);

	void create_Ika(Vec2 _init_p=Vec2(240.0,240.0),
		ControllerType _contoroller_type=ControllerType::PLAYER_1,
		Color _color=Setting::get_color(Setting::get_ika_1_team()),
		TeamType _team_type=Setting::get_ika_1_team(),
		CharType _char_type=Setting::get_char_1(),
		SpecialType _special_type=Setting::get_special_1());
	void create_Ika(int _index,Vec2 _pos);

	void create_Tire(Vec2 _pos);

	void create_Rumba(Vec2 _pos, Color _color);

	void create_Inkball(Vec2 _pos, double _init_height, Vec2 _dir, double _fly_strength, Color _color);

	//-----------------------------------------------Create関数--------------------------------------------------------------------------

	//メッセージの受け取り関数
	bool handle_message(const Telegram& _msg)override;
	//メッセージの仕分けを行う関数


	//管理オブジェクトのIDによる探索
	Entity* get_entity_from_id(ID _id)override;

	//--------MAP関数-----
	void set_map(MapType);
	void destroy_map();
	//使う予定はない
	//連続バトル的なモードがあれば使用する？
	//Mapサブクラスから呼び出す
	void change_map(Map*);

	Map* get_map() { return m_map; };
private:
	//ここでメッセージに対応する処理を呼び出す
	bool on_message(const Telegram& _msg);

	//衝突判定関数
	void check_collide();

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

	//update関数始めでオブジェクトの登録を行う
	void register_object();
private:
	//未登録オブジェクトを格納する
	//register_objcet()で登録される
	std::queue<Object*> m_yet_objects;

	//オブジェクトのインスタンス（のポインタ）を格納する
	std::vector<Object*> m_objects;

	//<そのObjectのdepth	,	そのObjectのポインタ>
	//動的に変化するものは並び替えられない
	typedef std::pair<int&, Object*> Drawer;

	//object.m_depth基準で並び替える
	//値が大きいほど手前に描画される
	std::vector<Drawer> m_objects_drawer;

	//mapインスタンス
	Map* m_map = nullptr;

	int m_timer = 0;

	//描画順のソート間隔(フレーム)
	int m_sort_duration = 1;
};						 



ObjectManager* Singleton<ObjectManager>::instance = nullptr;
