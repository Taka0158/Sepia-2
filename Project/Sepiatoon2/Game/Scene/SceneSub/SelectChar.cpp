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

	input();

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

	draw_charcter();

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

void SelectChar::toggle_ready()
{
	//ふたりプレイの場合
	if (Setting::get_is_single_play()==false)
	{
		if ((Setting::is_clicked_key_decide_p2()))
		{
			m_is_ready_p2 = !m_is_ready_p2;
			decide_p2(CharType(m_index_p2));
		}
	}

	if ((Setting::is_clicked_key_decide_p1()))
	{
		m_is_ready_p1 = !m_is_ready_p1;
		decide_p1(CharType(m_index_p1));
	}

}

void SelectChar::input()
{
	toggle_ready();

	if (!m_is_ready_p1)
	{
		if (Setting::is_clicked_key_right_p1())
		{
			m_index_p1++;
		}
		if (Setting::is_clicked_key_left_p1())
		{
			m_index_p1--;
		}
	}

	if (!m_is_ready_p2)
	{
		if (Setting::is_clicked_key_right_p2())
		{
			m_index_p2++;
		}
		if (Setting::is_clicked_key_left_p2())
		{
			m_index_p2--;
		}
	}

	m_index_p1 = clamp(m_index_p1, 0, 1);
	m_index_p2 = clamp(m_index_p2, 0, 1);
}


void SelectChar::draw_charcter()
{
	draw_frame();
}

void SelectChar::draw_frame()
{
	Size sc = Setting::get_size();
	int sc_h = Setting::get_size().y;
	int sc_w = Setting::get_size().x;
	Size sc_center = sc / 2;

	//額縁(キャラクタ)中心
	Size sc_center_p1 = Point(sc.x / 4 * 3, sc.y/2  -128*Setting::get_sc_scale());
	Size sc_center_p2 = Point(sc.x / 4, sc.y / 2	-128*Setting::get_sc_scale());

	//真ん中の区切りを描画
	int rect_w = 16;
	Rect(Point(sc_center.x - rect_w/2, 0), rect_w, sc_h).draw(Palette::Black);

	//額縁の描画
	ASSET_FAC->get_tex(ImageType::FRAME).drawAt(sc_center_p1);
	ASSET_FAC->get_tex(ImageType::FRAME).drawAt(sc_center_p2);

	//indexのキャラクタ表示
	get_tex(CharType(m_index_p1))->scale(0.5*Setting::get_sc_scale()).drawAt(sc_center_p1);
	get_tex(CharType(m_index_p2))->scale(0.5*Setting::get_sc_scale()).drawAt(sc_center_p2);

	//準備完了なら
	if (m_is_ready_p1)
	{
		darken_screen(1, Setting::get_size());
	}
	if (m_is_ready_p2)
	{
		darken_screen(2, Setting::get_size());
	}

	//文字描画
	FONT_IKA_KANA(96)(L"キャラクターせんたく").drawCenter(sc_center.x, 112, Palette::White);

	//キャラの説明
	chara_describe();

}

void SelectChar::decide_p1(CharType _type)
{
	Setting::set_char_1(_type);
}
void SelectChar::decide_p2(CharType _type)
{
	Setting::set_char_3(_type);
}

Texture* SelectChar::get_tex(CharType _type)
{
	Texture* ret = nullptr;
	switch (_type)
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

void SelectChar::chara_describe()
{
	Size sc = Setting::get_size();
	int sc_h = Setting::get_size().y;
	int sc_w = Setting::get_size().x;
	Size sc_center = sc / 2;

	//額縁(キャラクタ)中心
	Size sc_center_p1 = Point(sc.x / 4 * 3, sc.y / 2 - 128 * Setting::get_sc_scale());
	Size sc_center_p2 = Point(sc.x / 4, sc.y / 2 - 128 * Setting::get_sc_scale());

	//文字のy間隔
	int interval_y = 48;
	//sc_centerからどれだけx,y座標離れた位置から描画するか
	int init_y = 256;
	int init_x = -256;

	std::vector<String> p1_exp;
	std::vector<String> p2_exp;
	get_char_info(p1_exp, CharType(m_index_p1));
	get_char_info(p2_exp, CharType(m_index_p2));

	for (unsigned int i = 0; i < 5; i++)
	{
		FONT_IKA_KANA(32)(p1_exp[i]).draw(sc_center_p1.x + init_x, sc_center_p1.y + init_y + i*interval_y);
		FONT_IKA_KANA(32)(p2_exp[i]).draw(sc_center_p2.x + init_x, sc_center_p2.y + init_y + i*interval_y);
	}
}
void SelectChar::get_char_info(std::vector<String>& _container,CharType _type)
{
	CharTypeInfo p = CharTypeInfo(_type);
	String p_name =		 L"しゅるい----" + p.name;
	String p_hp =		 L"たいりょく---" + p.hp;
	String p_speed =	 L"すばやさ----" + p.speed;
	String p_gauge =	 L"たまりやすさ--" + p.special_gauge;
	String p_remark =	 L"とくちょう---" + p.remark;
	_container.push_back(p_name);
	_container.push_back(p_hp);
	_container.push_back(p_speed);
	_container.push_back(p_gauge);
	_container.push_back(p_remark);
}