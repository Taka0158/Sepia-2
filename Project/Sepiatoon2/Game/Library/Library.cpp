//--------------------------------------------列挙型-------------------------------------

enum class SceneType
{
	GAMEMAIN,
	MANUAL,
	OPTION,
	RESULT,
	SELECTCHAR,
	SELECTMAP,
	SELECTPLAYMODE,
	SELECTWEAPON,
	TESTWORLD,
	TITLE
};

enum class TeamType
{
	TEAM_A,
	TEAM_B
};

enum class CharType
{
	NORMAL=0,
	OCTOPUS
};

enum class SpecialType
{
	UNKNOWN,
	TYPHOON,
	DASH,
	SUPERNOVA
};

enum class MapType
{
	SIMPLE
};

enum class PlayModeType
{
	ONE_ON_ONE
};

enum class ControllerType
{
	PLAYER_1,
	PLAYER_2,
	CPU
};


enum class ImageType {
	MAP_SIMPLE = 0,
	INK_0_128,
	INK_1_128,
	INK_2_128,
	INK_3_128,
	INK_4_128,
	INK_5_128,
	INK_0_600,
	IKA_N_A,
	IKA_N_C,
	IKA_N_N,
	IKA_N_S,
	SCENESWITCH_1,
	SCENESWITCH_1_BG,
	SCENESWITCH_IKA,
	IKA_CUTIN,
	SHADOW_64,
	TIRE_64,
	ANIM_TYPHOON,
	RUMBA,
	INKBALL,
	ANIM_EXPLOSION_READY,
	ANIM_EXPLOSION,
	TITLE_BG,
	TITLE_IKA_BG,
	TITLE_LOGO,
	TACO_N_A,
	TACO_N_C,
	TACO_N_N,
	TACO_N_S,
	FRAME
};

enum class MovieType
{
	//CUTIN_IKA
};

enum class IkaStateType {
	IKA_UNDEFINED,
	IKA_NORMAL,
	IKA_SWIM,
	IKA_SINK,
	IKA_DAMAGED,
	IKA_SPECIAL_TYPHOON,
	IKA_SPECIAL_DASH,
	IKA_SPECIAL_SUPERNOVA
};

enum class CutInType
{
	IKA_CUTIN
};

enum class SceneSwitchType
{
	IKAIKA,
	IKA,
	FADEIN_FADEOUT
};




//シーン切り替えクラスSceneSwitchの状態を定義
enum class SwitchType {
	FIRST,
	SWITCH,
	SECOND,
	END
};

//--------------------------------------------列挙型-------------------------------------



//TODO

struct CharTypeInfo
{
	CharTypeInfo(CharType _type)
	{
		switch (_type)
		{
		case CharType::NORMAL:
			name = L"イカ";
			hp = L"ふつう";
			speed = L"ふつう";
			special_gauge = L"ふつう";
			remark = L"へいぼん";
			break;
		case CharType::OCTOPUS:
			name = L"タコ";
			hp = L"よわい";
			speed = L"すこしよわい";
			special_gauge = L"つよい";
			remark = L"よくすべる";
			break;
		}
	}
	//タイプの名前
	String name;
	//ゲーム内パラメータの評価
	String hp;
	String speed;
	String special_gauge;
	//備考
	String remark;
};

struct SceneParam
{
	SceneParam(SceneType _scene_type, SceneSwitchType _switch_type):st(_scene_type), sst(_switch_type) {};
	SceneType st;
	SceneSwitchType sst;
};

typedef std::bitset<32> ID;

class Paint
{
public:
	Paint()
	{
		pos = Point(0.0, 0.0);
		color = Color(Palette::White);
		scale = 1.0;
	}
	Paint(Point _p, Color _c,double _s=1.0):pos(_p), color(_c),scale(_s) {};
	Point pos;
	Color color;
	double scale;
};

struct InkballParm
{
	InkballParm(Vec2 _pos, double _init_height, Vec2 _dir, double _fly_strength, Color _color) :pos(_pos),
		init_height(_init_height),
		dir(_dir),
		fly_strength(_fly_strength),
		color(_color) {};
	Vec2 pos;
	double init_height;
	Vec2 dir;
	double fly_strength;
	Color color;
};

Vec2 Point_to_Vec2(Point _p)
{
	return Vec2(_p.x, _p.y);
}

Point Vec2_to_Point(Vec2 _v)
{
	return Point(_v.x, _v.y);
}

//右方向の垂直ベクトルを返す
Vec2 perp(Vec2 _vec)
{
	return Vec2(-_vec.y, _vec.x);
}

template <class T>
T clamp(T _val,T _min,T _max)
{
	return Min(_max, Max(_val, _min));
};

Point clamp(Point _val, Point _min, Point _max)
{
	return Point(Min(_max.x, Max(_val.x, _min.x)), Min(_max.y, Max(_val.y, _min.y)));
};

Vec2 clamp(Vec2 _val, Vec2 _min, Vec2 _max)
{
	return Vec2(Min(_max.x, Max(_val.x, _min.x)), Min(_max.y, Max(_val.y, _min.y)));
};

//IDを16進数表記に
//bitset　は　右から[0][1]...
char hex_c[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
String to_hex(ID _id)
{
	String ret=L"xxxxxxxx";
	int j = 0;
	for (int i = 7; i >= 0; i--,j++)
	{
		ret[j] = hex_c[_id[i * 4] + _id[i * 4 + 1] * 2 + _id[i * 4 + 2] * 4 + _id[i * 4 + 3]*8];
	}
	return ret;
}

bool is_same_color(const Color& _c1, const Color& _c2)
{
	int r1 = _c1.r, g1 = _c1.g, b1 = _c1.b;
	int r2 = _c2.r, g2 = _c2.g, b2 = _c2.b;
	int dr = abs(r1 - r2);
	int dg = abs(g1 - g2);
	int db = abs(b1 - b2);
	int sum = dr + dg + db;
	return (sum <= COLOR_THRESHOLD);
}

bool is_same_class(ID _id1, ID _id2)
{
	std::bitset<16> b16_1;
	std::bitset<16> b16_2;
	for (int i = 0; i < 16; i++)
	{
		b16_1[i] = _id1[i + 16];
		b16_2[i] = _id2[i + 16];
	}
	return (b16_1 == b16_2);
}

Vec2 get_Vec2(Vec2 _from, Vec2 _to)
{
	return Vec2(_to.x - _from.x, _to.y - _from.y);
}

//エフェクトに使用 要素数ではなくindex指定に注意
int get_tex_loop_index(int& _now_image_index,int _max_index, int _loop_start_index, int _loop_end_index, bool _is_loop)
{
	if (_max_index < _loop_end_index)ASSERT(L"get_tex_loop_index : 無効な引数");

	int next_index = 0;

	next_index = _now_image_index + 1;

	//ループ中なら
	if (_is_loop)
	{
		if (_loop_end_index < next_index)
		{
			next_index = _loop_start_index;
		}
	}
	next_index = clamp(next_index, 0, _max_index);
	return next_index;
}

//_c1 (0.0----_r----1) _c2
Color blend_color(Color _c1, Color _c2 ,double _r)
{
	_r = clamp(_r, 0.0, 1.0);
	return Color(_c1.r*(1 - _r) + _c2.r*_r,
		_c1.g*(1 - _r) + _c2.g*_r,
		_c1.b*(1 - _r) + _c2.b*_r,
		_c1.a*(1 - _r) + _c2.a*_r);
}

//valueが[]範囲内に入っていればtrue
bool check_range(double _value, double _min, double _max)
{
	return (_min <= _value && _value <= _max);
}

//画面 1:右半分 2:左半分　を暗転させる
void darken_screen(int index ,Size _sc_size)
{
	if (index != 1)
	{
		Rect(Point(0.0, 0.0), Size(_sc_size.x / 2, _sc_size.y)).draw(Color(Palette::Black, 200));
	}
	else
	{
		Rect(Point(_sc_size.x / 2, 0.0), Size(_sc_size.x / 2, _sc_size.y)).draw(Color(Palette::Black, 200));
	}
}