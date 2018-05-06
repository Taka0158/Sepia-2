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
	TYPHOON=0,
	DASH,
	SUPERNOVA
};

enum class MapType
{
	SIMPLE=0,
	SIMPLE_BIG,
	CLASSIC
};

enum class MissileType
{
	NORMAL=0,
	RAIN
};

enum class OrbType
{
	NORMAL=0,
	SPECIAL
};

enum class IkaBalloonType
{
	ITEM=0,
	ORB
};

enum class PlayModeType
{
	//							(Settingでの添字)
	P1_VS_COM = 0,	//PC			1vs2
	P1_COM_VS_COM_COM,	//PCCC		1,2vs3,4
	P1_VS_P2,			//PP		1 vs 3
	P1_COM_VS_P2_COM,	//PCPC		1,2 vs 3,4
	P1_P2_VS_COM_COM	//PPCC		1,3 vs 2,4
};

enum class ControllerType
{
	PLAYER_1,
	PLAYER_2,
	CPU
};

enum class ItemType
{
	MULTI_MISSILE=0,
	RAIN,
	RUMBA
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
	FRAME,
	ANIM_SELECT_SUPERNOVA,
	ANIM_SELECT_TYPHOON,
	MAP_SIMPLE_BIG,
	WALL,
	WALL_BLACK,
	MAP_CLASSIC,
	MAP_CLASSIC_SAMPLE,
	ANIM_ORB,
	ANIM_CUTIN_WIND,
	ANIM_SELECT_DASH,
	MISSILE,
	TRAMPOLINE,
	SPECIAL_ORB,
	IKA_BALLOON_1,
	IKA_BALLOON_2,
	RESPAWN_POINT,
	WALL_BLACK_CIRCLE

};

enum class MapGimmickType
{
	NONE = 0,
	WALL ,
	TRAMPOLINE,
	RESPAWN_A,
	RESPAWN_B,
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
	IKA_SPECIAL_SUPERNOVA,
	IKA_RESPAWN
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



struct MapTypeInfo
{
	MapTypeInfo(MapType _type)
	{
		switch (_type)
		{
		case MapType::SIMPLE:
			name = L"シンプル";
			remark_1 = L"なにもおこらないシンプルなマップ";
			remark_2 = L"はじめてにはもってこい！";
			break;
		case MapType::SIMPLE_BIG:
			name = L"シンプル(ビッグサイズ)";
			remark_1 = L"なにもおこらないシンプルなマップ";
			remark_2 = L"ひろい！";
			break;
		case MapType::CLASSIC:
			name = L"クラシックマップ";
			remark_1 = L"こうじ";
			remark_2 = L"こうじ";
			break;
		}
	}
	//マップの名前
	String name;
	//説明
	String remark_1;
	String remark_2;
};

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
			speed = L"ふつう";
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

struct SpecialTypeInfo
{
	SpecialTypeInfo(SpecialType _type)
	{
		switch (_type)
		{
		case SpecialType::TYPHOON:
			name = L"タイフーン";
			remark = L"だれもちかづけない！";
			break;
		case SpecialType::SUPERNOVA:
			name = L"だいばくはつ";
			remark = L"いっきにぎゃくてん！";
			break;
		case SpecialType::DASH:
			name = L"バリアダッシュ";
			remark = L"ムテキになってかけぬけろ！";
			break;
		}
	}
	//タイプの名前
	String name;
	//説明
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
	Paint(Point _p, Color _c,double _s=1.0,Image* _b=nullptr,bool _is_rotate=true):pos(_p), color(_c),scale(_s),blend_im(_b),is_rotate(_is_rotate) {};
	Point pos;
	Color color;
	double scale;
	//指定のインク画像があれば差し込む
	Image* blend_im;
	bool is_rotate;
};

struct MissileParm
{
	MissileParm(Vec2 _pos, double _init_height, Color _color,bool _is_rising=true,MissileType _type=MissileType::NORMAL) :pos(_pos),
		init_height(_init_height),
		color(_color),
		is_rising(_is_rising),
		type(_type){};
	Vec2 pos;
	double init_height;
	Color color;
	//上昇中かどうか
	bool is_rising;
	MissileType type;
};

struct InkballParm
{
	InkballParm(Vec2 _pos, double _init_height, Vec2 _dir, double _fly_strength, Color _color,double _paint_scale=1.0)
		:pos(_pos),
		init_height(_init_height),
		dir(_dir),
		fly_strength(_fly_strength),
		color(_color),
		paint_scale(_paint_scale){};
	Vec2 pos;
	double init_height;
	Vec2 dir;
	double fly_strength;
	Color color;
	double paint_scale;
};

struct IkaBalloonParm
{
	IkaBalloonParm(Vec2 _pos,IkaBalloonType _type):pos(_pos),type(_type) {};
	Vec2 pos;
	IkaBalloonType type;
};

struct RumbaParm
{
	RumbaParm(Vec2 _pos, Color _color) :pos(_pos), color(_color) {};
	Vec2 pos;
	Color color;
};

struct OrbParm
{
	OrbParm(Vec2 _pos, double _init_height, Vec2 _dir, double _fly_strength, OrbType _type=OrbType::NORMAL)
		:pos(_pos),
		init_height(_init_height),
		dir(_dir),
		fly_strength(_fly_strength),
		type(_type){};
	Vec2 pos;
	double init_height;
	Vec2 dir;
	double fly_strength;
	OrbType type;
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

int ctoi(char c) 
{
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	return 0;
}

namespace collide
{
	//コリジョンマスクのAABBの左上座標と右下座標を返す
	std::pair<Point,Point> get_bounding_box(Circle _mask)
	{
		std::pair<Point, Point> ret;
		Point lt, rb;
		int r = _mask.r;
		int x = _mask.x;
		int y = _mask.y;
		lt = Point(x - r, y - r);
		rb = Point(x + r, y + r);
		return ret = std::make_pair(lt, rb);
	}

	//点座標からどの番号（モートン順序）に所属するかを返す 0オリジン
	int get_morton_order_from_index(Point _p)
	{
		//分割最小空間の一片の大きさ
		double w = COLLIDE_SPACE_WIDTH / Pow(2, COLLIDE_SPACE_MAX_PARTITION_LEVEL);
		double h = COLLIDE_SPACE_HEIGHT / Pow(2, COLLIDE_SPACE_MAX_PARTITION_LEVEL);

		int index_x = _p.x / w;
		int index_y = _p.y / h;

		Bitset x = index_x;
		Bitset y = index_y;
		Bitset b;
		b.reset();

		for (int i = 0; i < COLLIDE_SPACE_MAX_PARTITION_LEVEL; i++)
		{
			int j = i * 2;
			b[j] = x[i];
			b[j + 1] = y[i];
		}
		int ret = clamp(int(b.to_ulong()),0, COLLIDE_MAX_INDEX_SIZE - 1);
		return ret;
	}

	//コリジョンマスクのボリュームを考慮した所属空間のレベルを返す
	int get_level_from_mask(Circle _mask)
	{
		int ret = COLLIDE_SPACE_MAX_PARTITION_LEVEL;

		std::pair<Point, Point> p = get_bounding_box(_mask);
		Point lt, rb;
		lt = p.first;
		rb = p.second;
		lt = clamp(lt, COLLIDE_ROOT_SPACE_LT, COLLIDE_ROOT_SPACE_LT + Point(COLLIDE_SPACE_WIDTH-1, COLLIDE_SPACE_HEIGHT-1));
		rb = clamp(rb, COLLIDE_ROOT_SPACE_LT, COLLIDE_ROOT_SPACE_LT + Point(COLLIDE_SPACE_WIDTH-1, COLLIDE_SPACE_HEIGHT-1));
		int lt_morton_order = get_morton_order_from_index(lt);
		int rb_morton_order = get_morton_order_from_index(rb);

		//Println(L"lt", lt_morton_order);
		//Println(L"rb", rb_morton_order);

		Bitset b;

		b = Bitset(lt_morton_order) ^
			Bitset(rb_morton_order);

		//Println(L"xor", b);

		for (int i = 0; i < COLLIDE_SPACE_MAX_PARTITION_LEVEL; i++)
		{
			int j = i * 2;
			if (b[j] != 0 || b[j + 1] != 0)
			{
				ret=COLLIDE_SPACE_MAX_PARTITION_LEVEL-i-1;
			}
		}
		return ret;
	}


	//モートン番号から所属空間内の番号を得る
	int get_num_from_morton_num(int _morton_num, int _level)
	{
		Bitset tmp = _morton_num;

		Bitset  ret = (tmp >> ((COLLIDE_SPACE_MAX_PARTITION_LEVEL - _level) * 2));

		return int(ret.to_ulong());

	}

	//モートン番号と所属空間から配列木構造に格納すべきindexを得る
	int get_index_form_morton_num_and_level(int _morton_num, int _level)
	{
		//4分木であるため
		int d = 4 - 1;
		int n = int(((Pow(4, _level) - 1 )/ d));
		int m = get_num_from_morton_num(_morton_num, _level);
		//Println(L"morton", m);
		//Println(L"addictive_num", n);
		//Println(L"index:", m + n);
		return m + n;
	}

}
