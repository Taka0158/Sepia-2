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

	//OBJ_MGR�̃I�u�W�F�N�g�����֐����Ăяo��
	void create_request(MapGimmickType , Vec2);

};

MapLoader* Singleton<MapLoader>::instance = nullptr;