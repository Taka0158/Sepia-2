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
	//フルスクリーンの場合を1.0とする 比率は16:9のみを想定
	static double get_sc_scale()
	{
		return double(sc_w) / double(full_sc_w);
	}

	//ストップウォッチ
	static Stopwatch stopwatch;

	static int32 get_ms()
	{
		return stopwatch.ms();
	}

	//解像度
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
	//ゲーム情報の保持
	//A・Bチームの色
	static Color m_color_A;
	static Color m_color_B;

	//チームの割り当て
	static TeamType m_ika_1;
	static TeamType m_ika_2;
	static TeamType m_ika_3;
	static TeamType m_ika_4;

	//キャラのタイプ
	static CharType m_char_1;
	static CharType m_char_2;
	static CharType m_char_3;
	static CharType m_char_4;

	//スペシャルタイプ
	static SpecialType m_special_1;
	static SpecialType m_special_2;
	static SpecialType m_special_3;
	static SpecialType m_special_4;

	//PLAYERかCPU
	static ControllerType m_controller_1;
	static ControllerType m_controller_2;
	static ControllerType m_controller_3;
	static ControllerType m_controller_4;


	//マップ
	static MapType m_map;

	//プレイモード
	static PlayModeType m_playmode;

};
Stopwatch Setting::stopwatch = Stopwatch();
Setting* Setting::instance = nullptr;

int Setting::sc_w = 640;
int Setting::sc_h = 480;

//ウィンドウ解像度
int Setting::window_sc_w = 640;
int Setting::window_sc_h = 480;

//フルスクリーン解像度
int Setting::full_sc_w = 1920;
int Setting::full_sc_h = 1080;

//A・Bチームの色
Color Setting::m_color_A = Color(Palette::Aqua);
Color Setting::m_color_B = Color(Palette::Orange);

//チームの割り当て
TeamType Setting::m_ika_1 = TeamType::TEAM_A;
TeamType Setting::m_ika_2 = TeamType::TEAM_A;
TeamType Setting::m_ika_3 = TeamType::TEAM_B;
TeamType Setting::m_ika_4 = TeamType::TEAM_B;

//キャラのタイプ
CharType Setting::m_char_1 = CharType::NORMAL;
CharType Setting::m_char_2 = CharType::NORMAL;
CharType Setting::m_char_3 = CharType::NORMAL;
CharType Setting::m_char_4 = CharType::NORMAL;

//スペシャルタイプ
SpecialType Setting::m_special_1 = SpecialType::TYPHOON;
SpecialType Setting::m_special_2 = SpecialType::TYPHOON;
SpecialType Setting::m_special_3 = SpecialType::SUPERNOVA;
SpecialType Setting::m_special_4 = SpecialType::TYPHOON;

//コントローラータイプ
ControllerType Setting::m_controller_1 = ControllerType::PLAYER_1;
ControllerType Setting::m_controller_2 = ControllerType::CPU;
ControllerType Setting::m_controller_3 = ControllerType::PLAYER_2;
ControllerType Setting::m_controller_4 = ControllerType::CPU;

//マップ
MapType Setting::m_map = MapType::SIMPLE;

//プレイモード
PlayModeType Setting::m_playmode = PlayModeType::ONE_ON_ONE;