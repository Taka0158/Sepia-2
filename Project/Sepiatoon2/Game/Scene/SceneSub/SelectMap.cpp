#include"SelectMap.h"

#include"SelectPlayMode.cpp"

SelectMap::SelectMap()
{
	scene_name = L"SelectMap";
	initialize();
}

SelectMap::~SelectMap()
{
	finalize();
}

void SelectMap::initialize()
{
	m_timer = 0;
	m_index = 0;
	init_background();
}

void SelectMap::finalize()
{

}

void SelectMap::enter()
{
	m_commands.push_back(new SetMapSimple());
}

void SelectMap::exit()
{
	for (unsigned int i = 0; i < m_commands.size(); i++)
	{
		if (m_commands[i] != nullptr)
		{
			delete m_commands[i];
			m_commands[i] = nullptr;
		}
	}
}

void SelectMap::update()
{
	m_timer++;

	update_ika_pos();

	common_input(0, int(m_commands.size() - 1));
}

void SelectMap::draw()
{
	draw_background();
	map_describe();
	draw_command(Point(512*Setting::get_sc_scale(),-128 * Setting::get_sc_scale()), 16);
}

void SelectMap::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new SelectWeapon());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectPlayMode());
	}
}

void SelectMap::debug_draw()
{
	Println(L"command-index : ", m_index);
}

Texture* SelectMap::get_tex(int _index)
{
	Texture* ret = nullptr;

	switch (MapType(_index))
	{
	case MapType::SIMPLE:
		ret = &ASSET_FAC->get_tex(ImageType::MAP_SIMPLE);
		break;
	}

	return ret;
}

void SelectMap::map_describe()
{
	//描画座標
	Size sc=Setting::get_size();
	int sc_h = sc.y;
	int sc_w = sc.x;
	Size sc_center = sc / 2;
	
	//画面中心からどれだけy方向にずれるか
	int dy=-128;

	//マップの全体図表示
	get_tex(m_index)->scale(0.5*Setting::get_sc_scale()).drawAt(sc_center.x, sc_center.y + dy);

	MapTypeInfo mti = MapTypeInfo(MapType(m_index));
	std::vector<String> exp;
	exp.push_back(mti.name);
	exp.push_back(mti.remark_1);
	exp.push_back(mti.remark_2);
	
	//マップの名前・説明を表示
	//y座標の間隔
	int interval_y = 72;
	//y座標の描画初期位置
	int init_y = sc_h / 2 + 256;
	for (unsigned int i = 0; i < exp.size();i++)
	{
		FONT_IKA_KANA(48)(exp[i]).drawCenter(sc_w / 2, init_y + i*interval_y);
	}
	
}