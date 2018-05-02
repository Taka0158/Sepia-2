#include"SelectChar.h"

#include"SelectWeapon.cpp"

SelectChar::SelectChar()
{
	scene_name = L"SelectChar";
	initialize();
}

SelectChar::~SelectChar()
{
	finalize();
}

void SelectChar::initialize()
{
	m_timer = 0;
	m_index = 0;
	init_background();

}

void SelectChar::finalize()
{

}

void SelectChar::enter()
{
	m_is_ready_p1 = false;

	if (Setting::get_is_single_play())m_is_ready_p2 = true;
	else m_is_ready_p2 = false;

	m_index_p1 = 0;
	m_index_p2 = 0;

	m_ready_timer = 0;
}

void SelectChar::exit()
{

}

void SelectChar::update()
{
	m_timer++;

	update_ika_pos();

	update_pos();

	input(ENUM_NUM_CHAR_TYPE-1);

	if (m_is_ready_p1&&m_is_ready_p2)
	{
		m_ready_timer++;
	}
	else
	{
		m_ready_timer = 0;
	}

	//両方が準備完了かつ一定時間経過でScene遷移
	if (m_ready_timer == m_ready_durtion)
	{
		SceneType next_scene_type = SceneType::SELECTWEAPON;
		SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
		SceneParam sp = SceneParam(next_scene_type, switch_type);
		MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
	}
}

void SelectChar::draw()
{
	draw_background();

	draw_sub(L"キャラクターせんたく");

}

void SelectChar::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new Title());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectWeapon());
	}
}

void SelectChar::debug_draw()
{
	CharTypeInfo p1 = CharTypeInfo(Setting::get_char_1());
	CharTypeInfo p2 = CharTypeInfo(Setting::get_char_3());

	Println(L"P1->chartype", p1.name);
	Println(L"P2->chartype", p2.name);
	Println(L"P1->index ", m_index_p1);
	Println(L"P2->index ", m_index_p2);
}


Texture* SelectChar::get_tex(int _index)
{
	Texture* ret = nullptr;
	switch (CharType(_index))
	{
	case CharType::NORMAL:
		ret = &ASSET_FAC->get_tex(ImageType::IKA_N_N);
		break;
	case CharType::OCTOPUS:
		ret = &ASSET_FAC->get_tex(ImageType::TACO_N_N);
		break;
	}
	return ret;
}

void SelectChar::object_describe()
{
	//文字のy間隔
	int interval_y = 48;
	//sc_centerからどれだけx,y座標離れた位置から描画するか
	int init_y = 256;
	int init_x = -256;

	std::vector<String> p1_exp;
	std::vector<String> p2_exp;
	get_info(p1_exp, m_index_p1);
	get_info(p2_exp, m_index_p2);

	for (unsigned int i = 0; i < p1_exp.size(); i++)
	{
		FONT_IKA_KANA(32)(p1_exp[i]).draw(sc_center_p1.x + init_x, sc_center_p1.y + init_y + i*interval_y);
		FONT_IKA_KANA(32)(p2_exp[i]).draw(sc_center_p2.x + init_x, sc_center_p2.y + init_y + i*interval_y);
	}
}