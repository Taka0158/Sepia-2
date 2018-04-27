#include"Tire.h"

Tire::Tire(Map* _map,Vec2 _init_pos) :MapGimmick(ID(ID_MAPGIMMCIK_TIRE))
{
	m_map = _map;
	init_moving_param();
	set_id();
	initialize();
	m_pos = _init_pos;

	set_moving_parm();
}

Tire::~Tire()
{

}

void Tire::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = 0;
	m_init_depth = 0;
	m_mask_radius = 32.0;
}

void Tire::finalize()
{

}

void Tire::update()
{

	behavior_update();

	mask_update();

	restrain();
}

void Tire::draw()
{
	ASSET_FAC->get_tex(ImageType::TIRE_64).drawAt(m_pos);
}

void Tire::debug_update()
{

}

void Tire::debug_draw()
{
	m_mask.drawFrame(1.0,0.0,Palette::Red);
	FONT_DEBUG_8(to_hex(m_id)).drawCenter(m_pos, Palette::Black);
}

void Tire::set_id()
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
void Tire::init_id()
{
	m_next_valid_id = 0;
}


bool Tire::handle_message(const Telegram& _msg)
{
	//NONE
	return true;
}

bool Tire::handle_collide(Object* _obj)
{
	on_collide(_obj);
	return true;
}

bool Tire::on_collide(Object* _obj) 
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		switch (other->get_ika_fsm()->get_now_state())
		{
		case IkaStateType::IKA_SPECIAL_TYPHOON:
			burst(get_Vec2(other->get_p(), m_pos)*3);
			break;
		case IkaStateType::IKA_SPECIAL_SUPERNOVA:
			burst(get_Vec2(other->get_p(), m_pos) * 10);
			break;
		}
		ret = true;
	}
	else if (Tire* other = dynamic_cast<Tire*>(_obj))
	{
		burst(clamp(get_Vec2(other->get_p(), m_pos),Vec2(-5.0,-5.00),Vec2(5.0,5.0)));
	}
	ret = true;

	return ret;
}

void Tire::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void Tire::behavior_update()
{


	//摩擦による速度の減算
	if (m_height <= 0.2)m_velocity -= m_velocity*m_friction;

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


void Tire::restrain()
{
	Size s = m_map->get_map_size();

	if (m_pos.x < 0 || s.x < m_pos.x)m_velocity.x = m_velocity.x*-1;
	if (m_pos.y < 0 || s.y < m_pos.y)m_velocity.y = m_velocity.x*-1;
	
	m_pos = clamp(m_pos, Vec2(0.0, 0.0), Vec2(s));
}