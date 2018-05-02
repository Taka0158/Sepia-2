#pragma once


class Setting :public Singleton<Setting>
{
	friend class Singleton<Setting>;
private:
	Setting()
	{
		stopwatch.start();

		Graphics::SetBackground(Palette::Black);

		toggle_fullscreen();
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
	static void set_ika_1_team(TeamType _type) { m_ika_1 = _type; }
	static void set_ika_2_team(TeamType _type) { m_ika_2 = _type; }
	static void set_ika_3_team(TeamType _type) { m_ika_3 = _type; }
	static void set_ika_4_team(TeamType _type) { m_ika_4=_type; }
	static CharType get_char_1() { return m_char_1; }
	static CharType get_char_2() { return m_char_2; }
	static CharType get_char_3() { return m_char_3; }
	static CharType get_char_4() { return m_char_4; }
	static void set_char_1(CharType _type) { m_char_1 = _type; }
	static void set_char_2(CharType _type) { m_char_2 = _type; }
	static void set_char_3(CharType _type) { m_char_3 = _type; }
	static void set_char_4(CharType _type) { m_char_4 = _type; }
	static SpecialType get_special_1() { return m_special_1; }
	static SpecialType get_special_2() { return m_special_2; }
	static SpecialType get_special_3() { return m_special_3; }
	static SpecialType get_special_4() { return m_special_4; }
	static void set_special_1(SpecialType _type) { m_special_1=_type; }
	static void set_special_2(SpecialType _type) { m_special_2=_type; }
	static void set_special_3(SpecialType _type) { m_special_3=_type; }
	static void set_special_4(SpecialType _type) { m_special_4=_type; }
	static ControllerType get_controller_1() { return m_controller_1; }
	static ControllerType get_controller_2() { return m_controller_2; }
	static ControllerType get_controller_3() { return m_controller_3; }
	static ControllerType get_controller_4() { return m_controller_4; }
	static void set_controller_1(ControllerType _type) { m_controller_1=_type; }
	static void set_controller_2(ControllerType _type) { m_controller_2=_type; }
	static void set_controller_3(ControllerType _type) { m_controller_3=_type; }
	static void set_controller_4(ControllerType _type) { m_controller_4=_type; }
	static MapType get_map() { return m_map; }
	static void set_map(MapType _type){ m_map= _type; }
	static PlayModeType get_playmode() { return m_playmode; }
	static void set_playmode(PlayModeType _type) { m_playmode= _type; }
	static bool get_is_single_play() { return m_is_single_play; }
	static void set_is_single_play(bool _b) { m_is_single_play = _b; }

	//キー入力（キーボード/ゲームパッド）
	static bool is_pressed_key_up_p1() { return (m_key_up_p1.pressed|| Gamepad(0).y<-INPUT_THRESHOLD); };
	static bool is_pressed_key_down_p1() { return( m_key_down_p1.pressed || Gamepad(0).y>INPUT_THRESHOLD); };
	static bool is_pressed_key_right_p1() { return (m_key_right_p1.pressed || Gamepad(0).x>INPUT_THRESHOLD); };
	static bool is_pressed_key_left_p1() { return (m_key_left_p1.pressed || Gamepad(0).x<-INPUT_THRESHOLD); };
	static bool is_clicked_key_up_p1() { return (m_key_up_p1.clicked || check_range(Gamepad(0).y, -1.0 + INPUT_THRESHOLD, -INPUT_THRESHOLD)); };
	static bool is_clicked_key_down_p1() { return(m_key_down_p1.clicked || check_range(Gamepad(0).y,INPUT_THRESHOLD,1.0-INPUT_THRESHOLD)); };
	static bool is_clicked_key_right_p1() { return (m_key_right_p1.clicked || check_range(Gamepad(0).x, INPUT_THRESHOLD, 1.0 - INPUT_THRESHOLD)); };
	static bool is_clicked_key_left_p1() { return (m_key_left_p1.clicked || check_range(Gamepad(0).x, -1.0 + INPUT_THRESHOLD, -INPUT_THRESHOLD)); };
	static bool is_clicked_key_decide_p1() { return (m_key_decide_p1.clicked || Gamepad(0).button(0).clicked); };
	static bool is_pressed_key_up_p2() { return (m_key_up_p2.pressed || Gamepad(1).y<-INPUT_THRESHOLD); };
	static bool is_pressed_key_down_p2() { return(m_key_down_p2.pressed || Gamepad(1).y>INPUT_THRESHOLD); };
	static bool is_pressed_key_right_p2() { return (m_key_right_p2.pressed || Gamepad(1).x>INPUT_THRESHOLD); };
	static bool is_pressed_key_left_p2() { return (m_key_left_p2.pressed || Gamepad(1).x<-INPUT_THRESHOLD); };
	static bool is_clicked_key_up_p2() { return (m_key_up_p2.clicked || check_range(Gamepad(1).y, -1.0 + INPUT_THRESHOLD, -INPUT_THRESHOLD)); };
	static bool is_clicked_key_down_p2() { return(m_key_down_p2.clicked || check_range(Gamepad(1).y, INPUT_THRESHOLD, 1.0 - INPUT_THRESHOLD)); };
	static bool is_clicked_key_right_p2() { return (m_key_right_p2.clicked || check_range(Gamepad(1).x, INPUT_THRESHOLD, 1.0 - INPUT_THRESHOLD)); };
	static bool is_clicked_key_left_p2() { return (m_key_left_p2.clicked || check_range(Gamepad(1).x, -1.0 + INPUT_THRESHOLD, -INPUT_THRESHOLD)); };
	static bool is_clicked_key_decide_p2() { return (m_key_decide_p2.clicked || Gamepad(1).button(0).clicked); };

	static Key get_key_up_p1() { return m_key_up_p1; };
	static Key get_key_down_p1() { return m_key_down_p1; };
	static Key get_key_right_p1() { return m_key_right_p1; };
	static Key get_key_left_p1() { return m_key_left_p1; };
	static Key get_key_decide_p1() { return m_key_decide_p1; };
	static Key get_key_up_p2() { return m_key_up_p2; };
	static Key get_key_down_p2() { return m_key_down_p2; };
	static Key get_key_right_p2() { return m_key_right_p2; };
	static Key get_key_left_p2() { return m_key_left_p2; };
	static Key get_key_decide_p2() { return m_key_decide_p2; };

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

	//キー入力（キーボード)
	static Key m_key_up_p1;
	static Key m_key_down_p1;
	static Key m_key_right_p1;
	static Key m_key_left_p1;
	static Key m_key_decide_p1;

	static Key m_key_up_p2;
	static Key m_key_down_p2;
	static Key m_key_right_p2;
	static Key m_key_left_p2;
	static Key m_key_decide_p2;

	//マップ
	static MapType m_map;

	//プレイモード
	static PlayModeType m_playmode;

	//1人プレイ　か　二人プレイか
	static bool m_is_single_play;

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

//コントローラータイプ(固定)
ControllerType Setting::m_controller_1 = ControllerType::PLAYER_1;
ControllerType Setting::m_controller_2 = ControllerType::CPU;
ControllerType Setting::m_controller_3 = ControllerType::PLAYER_2;
ControllerType Setting::m_controller_4 = ControllerType::CPU;

//マップ
MapType Setting::m_map = MapType::SIMPLE;

//プレイモード
PlayModeType Setting::m_playmode = PlayModeType::P1_VS_COM;

bool Setting::m_is_single_play = true;

//キー入力（キーボード)
Key Setting::m_key_up_p1 = Input::KeyUp;
Key Setting::m_key_down_p1 = Input::KeyDown;
Key Setting::m_key_right_p1 = Input::KeyRight;
Key Setting::m_key_left_p1 = Input::KeyLeft;
Key Setting::m_key_decide_p1 = Input::KeyRShift;
Key Setting::m_key_up_p2 = Input::KeyW;
Key Setting::m_key_down_p2 = Input::KeyS;
Key Setting::m_key_right_p2 = Input::KeyD;
Key Setting::m_key_left_p2 = Input::KeyA;
Key Setting::m_key_decide_p2 = Input::KeyLShift;