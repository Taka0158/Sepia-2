#include"SelectWeapon.h"

#include"SelectMap.cpp"

SelectWeapon::SelectWeapon()
{
	scene_name = L"SelectWeapon";
	initialize();
}

SelectWeapon::~SelectWeapon()
{
	finalize();
}

void SelectWeapon::initialize()
{
	m_timer = 0;
	m_index = 0;
	update_pos();
	init_background();
}

void SelectWeapon::finalize()
{

}

void SelectWeapon::enter()
{
	m_is_ready_p1 = false;

	if (Setting::get_is_single_play())m_is_ready_p2 = true;
	else m_is_ready_p2 = false;

	m_index_p1 = 0;
	m_index_p2 = 0;

	m_ready_timer = 0;

	m_tex_index_p1 = 0;
	m_tex_index_p2 = 0;
}

void SelectWeapon::exit()
{

}

void SelectWeapon::update()
{
	m_timer++;

	update_ika_pos();
	update_pos();

	//アニメーション枚数が50以上にならないと想定
	m_tex_index_p1 = m_timer % 50;
	m_tex_index_p2 = m_timer % 50;

	input(ENUM_NUM_SPECIAL_TYPE - 1);

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
		SceneType next_scene_type = SceneType::SELECTPLAYMODE;
		SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
		SceneParam sp = SceneParam(next_scene_type, switch_type);
		MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
	}

}

void SelectWeapon::draw()
{
	draw_background();

	draw_sub(L"スペシャルせんたく");
}

void SelectWeapon::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new SelectChar());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectMap());
	}
}

void SelectWeapon::debug_draw()
{
	SpecialTypeInfo p1 = SpecialTypeInfo(Setting::get_special_1());
	SpecialTypeInfo p2 = SpecialTypeInfo(Setting::get_special_3());

	Println(L"P1->specialtype", p1.name);
	Println(L"P2->specialtype", p2.name);
	Println(L"P1->index ", m_index_p1);
	Println(L"P2->index ", m_index_p2);
}

void SelectWeapon::object_describe()
{
	//文字のy間隔
	int interval_y = 48;
	//sc_centerからどれだけx,y座標離れた位置から描画するか
	int init_y = 256;
	int init_x = 0;

	std::vector<String> p1_exp;
	std::vector<String> p2_exp;
	get_info(p1_exp, m_index_p1);
	get_info(p2_exp, m_index_p2);

	for (unsigned int i = 0; i < p1_exp.size(); i++)
	{
		FONT_IKA_KANA(32)(p1_exp[i]).drawCenter(sc_center_p1.x + init_x, sc_center_p1.y + init_y + i*interval_y);
		FONT_IKA_KANA(32)(p2_exp[i]).drawCenter(sc_center_p2.x + init_x, sc_center_p2.y + init_y + i*interval_y);
	}
}

void SelectWeapon::draw_object()
{
	get_tex(m_index_p1,m_tex_index_p1)->scale(1.5*Setting::get_sc_scale()).drawAt(sc_center_p1,Setting::get_color(Setting::get_ika_1_team()));
	get_tex(m_index_p2,m_tex_index_p2)->scale(1.5*Setting::get_sc_scale()).drawAt(sc_center_p2, Setting::get_color(Setting::get_ika_3_team()));
}

void SelectWeapon::get_info(std::vector<String>& _container, int _index)
{
	SpecialTypeInfo p = SpecialTypeInfo(SpecialType(_index));
	String p_name = p.name;
	String p_remark = p.remark;
	_container.push_back(p_name);
	_container.push_back(p_remark);
}

void SelectWeapon::decide_p1()
{
	Setting::set_special_1(SpecialType(m_index_p1));
}
void SelectWeapon::decide_p2()
{
	Setting::set_special_3(SpecialType(m_index_p2));
}


Texture* SelectWeapon::get_tex(int _index,int& _tex_index)
{
	Texture* ret = nullptr;

	switch (SpecialType(_index))
	{
	case SpecialType::TYPHOON:
		ret = &ASSET_FAC->get_tex(ImageType::ANIM_SELECT_TYPHOON, _tex_index);
		break;
	case SpecialType::SUPERNOVA:
		ret = &ASSET_FAC->get_tex(ImageType::ANIM_SELECT_SUPERNOVA, _tex_index);
		break;
	case SpecialType::DASH:
		ret = &ASSET_FAC->get_tex(ImageType::ANIM_SELECT_DASH, _tex_index);
		break;
	}

	return ret;
}