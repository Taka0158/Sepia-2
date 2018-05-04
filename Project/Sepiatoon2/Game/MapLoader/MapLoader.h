#pragma once


class MapLoader:public Singleton<MapLoader>,public Entity
{
	friend class Singleton<MapLoader>;
	virtual ~MapLoader() {};
	MapLoader():Entity(ID(UID_MAP_LOADER)) {};
public:
	
	bool handle_message(const Telegram& _msg)override;
private:
	bool on_message(const Telegram& _msg);

	void load_map(Map*);

	//OBJ_MGRのオブジェクト生成関数を呼び出す
	void create_request(MapGimmickType , Vec2);

};

MapLoader* Singleton<MapLoader>::instance = nullptr;