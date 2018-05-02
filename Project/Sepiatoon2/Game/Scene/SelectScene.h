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

	//m_index�̍ő�l�������Ɏ��
	virtual void input(int _max_index);


	virtual void set_cut_scene(CutInType, Color = Palette::White) {};
protected:
	//�V�[������������
	void draw_sub(String _name);

	//����`�悷��
	virtual void draw_object();

	//�`����W���X�V����
	virtual void update_pos();

	//����L�[�ɂ�鏀�������̐؂�ւ����s��
	void toggle_ready();

	//�I�𒆂̕\�����s��
	virtual void draw_frame();

	//�I���̌�����s��
	virtual void decide_p1();
	virtual void decide_p2();

	//�\�����̃L�����N�^�̉摜������Ă���
	virtual Texture* get_tex(int) { return nullptr; };

	//�I�𒆂̐������s��
	virtual void object_describe() = 0;

	//�����f�[�^�̓���
	virtual void get_info(std::vector<String>& _container, int);


	//������������̑҂�����
	static int m_ready_durtion;
	//������������̌o�ߎ���
	int m_ready_timer;

	//�������ł������ǂ���
	bool m_is_ready_p1;
	bool m_is_ready_p2;
	//�I�𒆂�index
	int m_index_p1;
	int m_index_p2;

	//�`����W
	Size sc;
	int sc_h;
	int sc_w;
	Size sc_center;

	//�z��(�L�����N�^)���S
	Size sc_center_p1;
	Size sc_center_p2;
};
/*-----------------------------------------
�֐����e��SelectChar�ɉ���������
-----------------------------------------*/


void SelectScene::update_pos()
{
	sc = Setting::get_size();
	sc_h = Setting::get_size().y;
	sc_w = Setting::get_size().x;
	sc_center = sc / 2;

	//�z��(�L�����N�^)���S
	sc_center_p1 = Point(sc.x / 4 * 3, sc.y / 2 - 128 * Setting::get_sc_scale());
	sc_center_p2 = Point(sc.x / 4, sc.y / 2 - 128 * Setting::get_sc_scale());
}


void SelectScene::toggle_ready()
{
	//�ӂ���v���C�̏ꍇ
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
	//�z���̕\��
	draw_frame();

	//���̕\��
	draw_object();

	//���������Ȃ�Ó]
	if (m_is_ready_p1)
	{
		darken_screen(1, Setting::get_size());
	}
	if (m_is_ready_p2)
	{
		darken_screen(2, Setting::get_size());
	}

	//�����`��
	FONT_IKA_KANA(96)(_name).drawCenter(sc_center.x, 112, Palette::White);

	//���̐���
	object_describe();
}

void SelectScene::draw_frame()
{

	//�^�񒆂̋�؂��`��
	int rect_w = 16;
	Rect(Point(sc_center.x - rect_w / 2, 0), rect_w, sc_h).draw(Palette::Black);

	//�z���̕`��
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
	String p_name = L"����邢----" + p.name;
	String p_hp = L"������傭---" + p.hp;
	String p_speed = L"���΂₳----" + p.speed;
	String p_gauge = L"���܂�₷��--" + p.special_gauge;
	String p_remark = L"�Ƃ����傤---" + p.remark;
	_container.push_back(p_name);
	_container.push_back(p_hp);
	_container.push_back(p_speed);
	_container.push_back(p_gauge);
	_container.push_back(p_remark);
}
