#include"SpecialOrb.h"

SpecialOrb::SpecialOrb(Map* _map,Vec2 _init_pos, double _init_height,Vec2 _dir, double _fly_strength,OrbType _type) :Item(ID(ID_OBJ_IKA_SPECIAL_ORB))
{
	set_id();
	initialize();

	m_map = _map;

	init_moving_param();
	m_direction = _dir;
	m_pos = _init_pos;
	m_type = _type;
	
	set_gauge_up_amount();
	set_moving_parm();
	m_height = _init_height;
	fly(_fly_strength);
}

SpecialOrb::~SpecialOrb()
{

}

void SpecialOrb::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = 1;
	m_init_depth = 1;
	m_mask_radius = 8.0;
	m_mask_height = 4.0;
}

void SpecialOrb::finalize()
{

}

void SpecialOrb::update()
{
	m_timer++;
	gravity();
	behavior_update();

	mask_update();

	restrain();
}

void SpecialOrb::draw()
{
	draw_shadow(0.5);
	ASSET_FAC->get_tex(ImageType::SPECIAL_ORB).scale(0.25).drawAt(get_pos_height());
}

void SpecialOrb::debug_update()
{

}

void SpecialOrb::debug_draw()
{
	m_mask.drawFrame(1.0, 0.0, Palette::Red);
}

void SpecialOrb::set_id()
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
void SpecialOrb::init_id()
{
	m_next_valid_id = 0;
}

bool SpecialOrb::handle_message(const Telegram& _msg)
{
	//NONE
	return true;
}

bool SpecialOrb::handle_collide(CollidableObject* _obj)
{
	on_collide(_obj);
	return true;
}

bool SpecialOrb::on_collide(CollidableObject* _obj)
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		other->increase_special_gauge(m_gauge_up_amount);
		destroy();
		ret = true;
	}
	else if (Inkball* other = dynamic_cast<Inkball*>(_obj))
	{
		ret = true;
	}
	else if (SpecialOrb* other = dynamic_cast<SpecialOrb*>(_obj))
	{
		ret = true;
	}
		//それ以外の動体に接触すると消滅
	else if (MovingObject* other = dynamic_cast<MovingObject*>(_obj))
	{
		destroy();
		ret = true;
	}
	return ret;
}

void SpecialOrb::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void SpecialOrb::behavior_update()
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


void SpecialOrb::restrain()
{
	Size s = m_map->get_map_size();

	//マップ外に出ると破壊
	if (m_pos.x < 0 || s.x < m_pos.x)destroy();
	if (m_pos.y < 0 || s.y < m_pos.y)destroy();

}
void SpecialOrb::destroy()
{
	m_is_alive = false;
}

void SpecialOrb::set_gauge_up_amount()
{
	switch (m_type)
	{
	case OrbType::NORMAL:
		m_gauge_up_amount = GAUGE_INCREASE_NORMAL_ORB;
		break;
	case OrbType::SPECIAL:
		m_gauge_up_amount = GAUGE_INCREASE_SPECIAL_ORB;
		break;
	}
}