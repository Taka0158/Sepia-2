#include"Inkball.h"

Inkball::Inkball(Map* _map, Vec2 _init_pos, double _init_height,Vec2 _dir, double _fly_strength, Color _color) :Item(ID(ID_OBJ_INKBALL))
{
	//バグ有り
	initialize();

	m_direction = _dir;
	m_color = _color;
	m_map = _map;
	init_moving_param();
	set_id();
	m_pos = _init_pos;

	set_moving_parm();
	m_height = _init_height;
	fly(_fly_strength);
}

Inkball::~Inkball()
{
	//DEBUG->regist(DebugText(1.0, L"-----------インクボールデストラクタ-----------"));

}

void Inkball::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = 1;
	m_init_depth = 1;
	m_mask_radius = 8.0;
	m_mask_height = 6.0;
}

void Inkball::finalize()
{

}

void Inkball::update()
{
	timer++;
	gravity();
	behavior_update();

	if (m_height < 2.0)
	{
		Paint p = Paint(Vec2_to_Point(m_pos), m_color, 0.75);
		MSG_DIS->dispatch_message(0.0, this, m_map, msg::TYPE::MAP_PAINT, &p,false);

		destroy();
	}

	mask_update();

	calc_angle(m_angle);

	restrain();
}

void Inkball::draw()
{
	draw_shadow(0.25);
	ASSET_FAC->get_tex(ImageType::INKBALL).scale(0.25).drawAt(m_pos+Vec2(0.0,-m_height),m_color);
}

void Inkball::debug_update()
{

}

void Inkball::debug_draw()
{
	m_mask.drawFrame(1.0, 0.0, Palette::Red);
}

void Inkball::set_id()
{
	if (m_next_valid_id < 0xFFFF)
	{
		m_id |= m_next_valid_id;
		m_next_valid_id++;
	}
	else
	{
		ASSERT(L"オブジェクトのID割り当てが上限を超えました");
	}
}
void Inkball::init_id()
{
	m_next_valid_id = 0;
}


bool Inkball::handle_message(const Telegram& _msg)
{
	//NONE
	return true;
}

bool Inkball::handle_collide(Object* _obj)
{
	on_collide(_obj);
	return true;
}

bool Inkball::on_collide(Object* _obj)
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		if (other->get_color() == m_color)
		{
		}
		else
		{
			other->damaged(20.0);
			destroy();
		}
		ret = true;
	}
	else if (Rumba* other = dynamic_cast<Rumba*>(_obj))
	{
		other->destroy();
		ret = true;
	}
	return ret;
}

void Inkball::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void Inkball::behavior_update()
{
	m_velocity = m_direction;

	//速度の制限
	if (m_velocity.length() > m_max_speed)
	{
		m_velocity.setLength(m_max_speed);
	}

	//座標の更新
	m_pos += m_velocity;

	//速度がゼロでなければ正面ベクトルを更新
	if (m_velocity.lengthSq() > 0.000001)
	{
		m_heading = m_velocity.normalized();
		m_side_heading = perp(m_heading);
	}
}


void Inkball::restrain()
{
	Size s = m_map->get_map_size();

	//マップ外に出ると破壊
	if (m_pos.x < 0 || s.x < m_pos.x)destroy();
	if (m_pos.y < 0 || s.y < m_pos.y)destroy();

}
void Inkball::destroy()
{
	m_is_alive = false;
}