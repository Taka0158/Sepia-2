#include"Rumba.h"

Rumba::Rumba(Map* _map, Vec2 _init_pos,Color _color) :Item(ID(ID_OBJ_RUMBA))
{
	m_color = _color;
	m_map = _map;
	init_moving_param();
	set_id();
	initialize();
	m_pos = _init_pos;

	set_moving_parm();
	set_direction();
	fly();
}

Rumba::~Rumba()
{

}

void Rumba::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = 0;
	m_init_depth = 0;
	m_mask_radius = 48.0;
	m_speed = 1.0;
	m_paint_interval = 10;
	m_mask_height = 5.0;
}

void Rumba::finalize()
{

}

void Rumba::update()
{
	timer++;
	gravity();
	behavior_update();

	if (m_height < 2.0)
	{
		if (timer%m_paint_interval == 0)
		{
			Paint p = Paint(Vec2_to_Point(m_pos), m_color, 0.75);

			MSG_DIS->dispatch_message(0.0, this, m_map, msg::TYPE::MAP_PAINT, &p,false);
		}
	}


	mask_update();

	calc_angle(m_angle);

	restrain();
}

void Rumba::draw()
{
	draw_shadow();
	ASSET_FAC->get_tex(ImageType::RUMBA).rotate(m_angle+0.5*Pi).drawAt(m_pos+Vec2(0.0,-m_height),m_color);
}

void Rumba::debug_update()
{

}

void Rumba::debug_draw()
{
	m_mask.drawFrame(1.0, 0.0, Palette::Red);
	FONT_DEBUG_8(to_hex(m_id)).drawCenter(m_pos, Palette::Black);
}

void Rumba::set_id()
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
void Rumba::init_id()
{
	m_next_valid_id = 0;
}


bool Rumba::handle_message(const Telegram& _msg)
{
	//NONE
	return true;
}

bool Rumba::handle_collide(Object* _obj)
{
	on_collide(_obj);
	return true;
}

bool Rumba::on_collide(Object* _obj)
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		if (other->get_color() == m_color)
		{
			burst(get_Vec2(other->get_p(), m_pos));
		}
		else
		{
			destroy();
		}
		ret = true;
	}
	else if (Rumba* other = dynamic_cast<Rumba*>(_obj))
	{
		burst(clamp(get_Vec2(other->get_p(), m_pos), Vec2(-5.0, -5.0), Vec2(5.0, 5.0)));
		ret = true;
	}
	else if (Tire* other = dynamic_cast<Tire*>(_obj))
	{
		burst(clamp(get_Vec2(other->get_p(), m_pos), Vec2(-5.0, -5.0), Vec2(5.0, 5.0)));
		ret = true;
	}

	return ret;
}

void Rumba::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void Rumba::behavior_update()
{


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


void Rumba::restrain()
{
	Size s = m_map->get_map_size();

	if (m_pos.x < 0 || s.x < m_pos.x)m_velocity.x = m_velocity.x*-1;
	if (m_pos.y < 0 || s.y < m_pos.y)m_velocity.y = m_velocity.x*-1;

	m_pos = clamp(m_pos, Vec2(0.0, 0.0), Vec2(s));
}

void Rumba::set_direction()
{
	m_direction = Vec2(Random(-1.0,1.0), Random(-1.0, 1.0)).normalize();
	m_velocity = m_direction;
}

void Rumba::destroy()
{
	m_is_alive = false;
}