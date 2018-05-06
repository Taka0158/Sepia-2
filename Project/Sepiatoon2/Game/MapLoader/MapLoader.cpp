#include"MapLoader.h"


bool MapLoader::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool MapLoader::on_message(const Telegram& _msg)
{
	bool ret = false;

	switch (_msg.msg)
	{
	case msg::TYPE::MAP_LOAD:
		Map* m= (Map*)_msg.extraInfo;
		load_map(m);
		ret = true;
		break;
	}
	return ret;
}

void MapLoader::load_map(Map* _map)
{
	String str=L"";
	int w=0, h=0;

	switch (_map->get_map_type())
	{
	case MapType::SIMPLE:
		str = L"Assets/MapData/Simple.txt";
		w = MAP_S_X_NUM;
		h = MAP_S_Y_NUM;
	case MapType::SIMPLE_BIG:
		str = L"Assets/MapData/SimpleBig.txt";
		w = MAP_L_X_NUM;
		h = MAP_L_Y_NUM;
		break;
	case MapType::CLASSIC:
		str = L"Assets/MapData/MapClassic.txt";
		w = MAP_L_X_NUM;
		h = MAP_L_Y_NUM;
		break;
	default:
		ASSERT(L"予期しないMapTypeです");
		break;
	}

	TextReader reader(str);

	if (reader.isOpened() == false)ASSERT(L"マップデータを読み込めません");

	String line;

	for (int y = 0; y < h; y++)
	{
		reader.readLine(line);
		for (int x = 0; x < w; x++)
		{
			char type = line[x];
			Vec2 pos = Vec2(MAP_GRID_WIDTH / 2.0 + MAP_GRID_WIDTH*x, MAP_GRID_HEIGHT / 2.0 + MAP_GRID_HEIGHT*y);
			create_request(MapGimmickType(ctoi(type)), pos);
		}
	}

}

void MapLoader::create_request(MapGimmickType _type,Vec2 _pos)
{
	switch (_type)
	{
	case MapGimmickType::NONE:		break;	case MapGimmickType::WALL:		OBJ_MGR->create_Wall(_pos);		break;
	case MapGimmickType::TRAMPOLINE:		OBJ_MGR->create_Trampoline(_pos);		break;
	case MapGimmickType::RESPAWN_A:		OBJ_MGR->create_RespawnPoint(_pos,TeamType::TEAM_A);		break;
	case MapGimmickType::RESPAWN_B:		OBJ_MGR->create_RespawnPoint(_pos, TeamType::TEAM_B);		break;
	default:
		ASSERT(L"予期しないMapGimmickTypeです");
		break;
	}
}