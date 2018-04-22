//TODO

typedef std::bitset<32> ID;

class Paint
{
public:
	Paint()
	{
		pos = Point(0.0, 0.0);
		color = Color(Palette::White);
	}
	Paint(Point _p, Color _c):pos(_p), color(_c) {};
	Point pos;
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