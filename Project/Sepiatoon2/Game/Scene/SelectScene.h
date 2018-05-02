#pragma once


class SelectScene :public Scene
{
public:
	virtual void initialize() = 0;
	virtual void  finalize() = 0;

	virtual void enter() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void exit() = 0;

	virtual void debug_update() = 0;
	virtual void debug_draw() = 0;

	//m_indexの最大値を引数に取る
	virtual void input(int _max_index);


	virtual void set_cut_scene(CutInType, Color = Palette::White) {};
protected:
	//シーン名を引数に
	void draw_sub(String _name);

	//主題を描画する
	virtual void draw_object();

	//描画座標を更新する
	virtual void update_pos();

	//決定キーによる準備完了の切り替えを行う
	void toggle_ready();

	//選択中の表示を行う
	virtual void draw_frame();

	//選択の決定を行う
	virtual void decide_p1();
	virtual void decide_p2();

	//表示中のキャラクタの画像を取ってくる
	virtual Texture* get_tex(int) { return nullptr; };

	//選択中の説明を行う
	virtual void object_describe() = 0;

	//説明データの入力
	virtual void get_info(std::vector<String>& _container, int);


	//準備完了からの待ち時間
	static int m_ready_durtion;
	//準備完了からの経過時間
	int m_ready_timer;

	//準備ができたかどうか
	bool m_is_ready_p1;
	bool m_is_ready_p2;
	//選択中のindex
	int m_index_p1;
	int m_index_p2;

	//描画座標
	Size sc;
	int sc_h;
	int sc_w;
	Size sc_center;

	//額縁(キャラクタ)中心
	Size sc_center_p1;
	Size sc_center_p2;
};
/*-----------------------------------------
関数内容はSelectCharに沿ったもの
-----------------------------------------*/


void SelectScene::update_pos()
{
	sc = Setting::get_size();
	sc_h = Setting::get_size().y;
	sc_w = Setting::get_size().x;
	sc_center = sc / 2;

	//額縁(キャラクタ)中心
	sc_center_p1 = Point(sc.x / 4 * 3, sc.y / 2 - 128 * Setting::get_sc_scale());
	sc_center_p2 = Point(sc.x / 4, sc.y / 2 - 128 * Setting::get_sc_scale());
}


void SelectScene::toggle_ready()
{
	//ふたりプレイの場合
	if (Setting::get_is_single_play() == false)
	{
		if ((Setting::is_clicked_key_decide_p2()))
		{
			m_is_ready_p2 = !m_is_ready_p2;
			decide_p2();
		}
	}

	if ((Setting::is_clicked_key_decide_p1()))
	{
		m_is_ready_p1 = !m_is_ready_p1;
		decide_p1();
	}

}

void SelectScene::input(int _max_index)
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

	m_index_p1 = clamp(m_index_p1, 0, _max_index);
	m_index_p2 = clamp(m_index_p2, 0, _max_index);
}

void SelectScene::draw_object()
{
	get_tex(m_index_p1)->scale(0.5*Setting::get_sc_scale()).drawAt(sc_center_p1, Setting::get_color(Setting::get_ika_1_team()));
	get_tex(m_index_p2)->scale(0.5*Setting::get_sc_scale()).drawAt(sc_center_p2, Setting::get_color(Setting::get_ika_3_team()));
}


void SelectScene::draw_sub(String _name)
{
	//額縁の表示
	draw_frame();

	//主題の表示
	draw_object();

	//準備完了なら暗転
	if (m_is_ready_p1)
	{
		darken_screen(1, Setting::get_size());
	}
	if (m_is_ready_p2)
	{
		darken_screen(2, Setting::get_size());
	}

	//文字描画
	FONT_IKA_KANA(96)(_name).drawCenter(sc_center.x, 112, Palette::White);

	//主題の説明
	object_describe();
}

void SelectScene::draw_frame()
{

	//真ん中の区切りを描画
	int rect_w = 16;
	Rect(Point(sc_center.x - rect_w / 2, 0), rect_w, sc_h).draw(Palette::Black);

	//額縁の描画
	ASSET_FAC->get_tex(ImageType::FRAME).drawAt(sc_center_p1);
	ASSET_FAC->get_tex(ImageType::FRAME).drawAt(sc_center_p2);
}

void SelectScene::decide_p1()
{
	Setting::set_char_1(CharType(m_index_p1));
}
void SelectScene::decide_p2()
{
	Setting::set_char_3(CharType(m_index_p2));
}


void SelectScene::get_info(std::vector<String>& _container, int _index)
{
	CharTypeInfo p = CharTypeInfo(CharType(_index));
	String p_name = L"しゅるい----" + p.name;
	String p_hp = L"たいりょく---" + p.hp;
	String p_speed = L"すばやさ----" + p.speed;
	String p_gauge = L"たまりやすさ--" + p.special_gauge;
	String p_remark = L"とくちょう---" + p.remark;
	_container.push_back(p_name);
	_container.push_back(p_hp);
	_container.push_back(p_speed);
	_container.push_back(p_gauge);
	_container.push_back(p_remark);
}
