#pragma once


class Setting :public Singleton<Setting>
{
	friend class Singleton<Setting>;
private:
	Setting()
	{
		stopwatch.start();

		Graphics::SetBackground(Palette::Gray);
	};
	~Setting() {};
public:
	static void window_resize(int w, int h)
	{
		Window::Resize(w, h);
		sc_w = w;
		sc_h = h;
	};
	static void toggle_fullscreen()
	{
		if (Window::IsFullSceen())
		{
			sc_w = window_sc_w;
			sc_h = window_sc_h;
			Window::SetFullscreen(false, Size(sc_w, sc_h));
			Window::SetBaseSize(sc_w, sc_h);
		}
		else
		{
			sc_w = full_sc_w;
			sc_h = full_sc_h;
			Window::SetFullscreen(true, Size(sc_w, sc_h));
			Window::SetBaseSize(sc_w, sc_h);
		}
	
	}
	static Size get_size()
	{
		return Size(sc_w, sc_h);
	};

	static Vec2 get_sc()
	{
		return Vec2(sc_w, sc_h);
	}
	//�t���X�N���[���̏ꍇ��1.0�Ƃ��� �䗦��16:9�݂̂�z��
	static double get_sc_scale()
	{
		return double(sc_w) / double(full_sc_w);
	}

	//�X�g�b�v�E�H�b�`
	static Stopwatch stopwatch;

	static int32 get_ms()
	{
		return stopwatch.ms();
	}

	//�𑜓x
	static int sc_w;
	static int sc_h;
	static int full_sc_w;
	static int full_sc_h;
	static int window_sc_w;
	static int window_sc_h;

	static Color get_color(TeamType _type) { return (_type==TeamType::TEAM_A)?m_color_A:m_color_B; }
	static TeamType get_ika_1_team() { return m_ika_1; }
	static TeamType get_ika_2_team() { return m_ika_2; }
	static TeamType get_ika_3_team() { return m_ika_3; }
	static TeamType get_ika_4_team() { return m_ika_4; }
	static CharType get_char_1() { return m_char_1; }
	static CharType get_char_2() { return m_char_2; }
	static CharType get_char_3() { return m_char_3; }
	static CharType get_char_4() { return m_char_4; }
	static SpecialType get_special_1() { return m_special_1; }
	static SpecialType get_special_2() { return m_special_2; }
	static SpecialType get_special_3() { return m_special_3; }
	static SpecialType get_special_4() { return m_special_4; }
	static ControllerType get_controller_1() { return m_controller_1; }
	static ControllerType get_controller_2() { return m_controller_2; }
	static ControllerType get_controller_3() { return m_controller_3; }
	static ControllerType get_controller_4() { return m_controller_4; }
	static MapType get_map(){ return m_map; }
	static PlayModeType get_playmode() { return m_playmode; }

private:
	//�Q�[�����̕ێ�
	//A�EB�`�[���̐F
	static Color m_color_A;
	static Color m_color_B;

	//�`�[���̊��蓖��
	static TeamType m_ika_1;
	static TeamType m_ika_2;
	static TeamType m_ika_3;
	static TeamType m_ika_4;

	//�L�����̃^�C�v
	static CharType m_char_1;
	static CharType m_char_2;
	static CharType m_char_3;
	static CharType m_char_4;

	//�X�y�V�����^�C�v
	static SpecialType m_special_1;
	static SpecialType m_special_2;
	static SpecialType m_special_3;
	static SpecialType m_special_4;

	//PLAYER��CPU
	static ControllerType m_controller_1;
	static ControllerType m_controller_2;
	static ControllerType m_controller_3;
	static ControllerType m_controller_4;


	//�}�b�v
	static MapType m_map;

	//�v���C���[�h
	static PlayModeType m_playmode;

};
Stopwatch Setting::stopwatch = Stopwatch();
Setting* Setting::instance = nullptr;

int Setting::sc_w = 640;
int Setting::sc_h = 480;

//�E�B���h�E�𑜓x
int Setting::window_sc_w = 640;
int Setting::window_sc_h = 480;

//�t���X�N���[���𑜓x
int Setting::full_sc_w = 1920;
int Setting::full_sc_h = 1080;

//A�EB�`�[���̐F
Color Setting::m_color_A = Color(Palette::Aqua);
Color Setting::m_color_B = Color(Palette::Orange);

//�`�[���̊��蓖��
TeamType Setting::m_ika_1 = TeamType::TEAM_A;
TeamType Setting::m_ika_2 = TeamType::TEAM_A;
TeamType Setting::m_ika_3 = TeamType::TEAM_B;
TeamType Setting::m_ika_4 = TeamType::TEAM_B;

//�L�����̃^�C�v
CharType Setting::m_char_1 = CharType::NORMAL;
CharType Setting::m_char_2 = CharType::NORMAL;
CharType Setting::m_char_3 = CharType::NORMAL;
CharType Setting::m_char_4 = CharType::NORMAL;

//�X�y�V�����^�C�v
SpecialType Setting::m_special_1 = SpecialType::TYPHOON;
SpecialType Setting::m_special_2 = SpecialType::TYPHOON;
SpecialType Setting::m_special_3 = SpecialType::SUPERNOVA;
SpecialType Setting::m_special_4 = SpecialType::TYPHOON;

//�R���g���[���[�^�C�v
ControllerType Setting::m_controller_1 = ControllerType::PLAYER_1;
ControllerType Setting::m_controller_2 = ControllerType::CPU;
ControllerType Setting::m_controller_3 = ControllerType::PLAYER_2;
ControllerType Setting::m_controller_4 = ControllerType::CPU;

//�}�b�v
MapType Setting::m_map = MapType::SIMPLE;

//�v���C���[�h
PlayModeType Setting::m_playmode = PlayModeType::ONE_ON_ONE;