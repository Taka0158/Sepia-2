#include"Missile.h"

Missile::Missile (Map* _map, Vec2 _init_pos, double _init_height, Color _color,MissileType _type):Item(ID(ID_OBJ_MISSILE))
{
	m_missile_type = _type;
	set_missile_parameter();

	initialize();

	m_pos = _init_pos;
	m_color = _color;
	m_map = _map;
	m_height = 100;
	init_moving_param();
	set_id();
	set_moving_parm();

	m_angle = 0;
	//吹っ飛ぶ
	fly(m_rising_speed);
}

Missile::~Missile()
{

}

void Missile::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = 2;
	m_init_depth = 2;
	m_mask_radius = 12.0;
	m_mask_height = 50.0;
	m_rising_speed = 100;

	//始めは重力を無視した挙動
	unable_gravity();
}


void Missile::set_missile_parameter()
{
	switch (m_missile_type)
	{
	case MissileType::NORMAL:
		m_scale = 0.5;
		break;
	case MissileType::RAIN:
		m_scale = 1.0;
		break;
	}
}


void Missile::finalize()
{

}

void Missile::update()
{
	m_timer++;
	gravity();
	behavior_update();

	if (m_height ==0)
	{
		Paint p = Paint(Vec2_to_Point(m_pos), m_color, 1.25);
		MSG_DIS->dispatch_message(0.0, this, m_map, msg::TYPE::MAP_PAINT, &p, false);
		destroy();
	}

	if (m_height > m_threshold)
	{
		reach_peak();
	}

	mask_update();

	restrain();
}

void Missile::draw()
{
	draw_shadow(0.5);
	ASSET_FAC->get_tex(ImageType::MISSILE).scale(m_scale).rotate(m_angle).drawAt(m_pos + Vec2(0.0, -m_height), m_color);

}

void Missile::debug_update()
{

}

void Missile::debug_draw()
{
	FONT_DEBUG_16(m_id).drawCenter(Vec2(m_pos.x, m_pos.y + 32));
	if (m_missile_type == MissileType::RAIN)Circle(m_pos, m_rain_area).drawFrame(3.0, 0.0, Palette::Red);
	m_mask.drawFrame(1.0, 0.0, Palette::Red);
}

void Missile::set_id()
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

void Missile::init_id()
{
	m_next_valid_id = 0;
}

bool Missile::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool  Missile::on_message(const Telegram& _msg)
{
	bool ret = false;

	switch (_msg.msg)
	{
	case msg::TYPE::GIVE_MISSILE_TARGET:
		m_target = (Object*)_msg.extraInfo;
		ret = true;
		break;
	}
	return ret;
}

bool Missile::handle_collide(CollidableObject* _obj)
{
	on_collide(_obj);
	return true;
}

bool Missile::on_collide(CollidableObject* _obj)
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		if (other->get_color() == m_color)
		{

		}
		else
		{
			other->damaged(MISSILE_DAMAGE);
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

void Missile::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void Missile::behavior_update()
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

void Missile::restrain()
{
	Size s = m_map->get_map_size();

	//マップ外に出ると破壊
	if (m_pos.x < 0 || s.x < m_pos.x)destroy();
	if (m_pos.y < 0 || s.y < m_pos.y)destroy();

	m_height = Max(m_height, 0.0);

}
void Missile::destroy()
{
	m_is_alive = false;
}

void Missile::turnaround()
{
	//誤差
	Vec2 tmp = RandomVec2(Random(-300, 300), Random(-300, 300));

	//ターゲットがいなければそのまま落ちる
	if(m_target!=nullptr)m_pos = m_target->get_p();
	m_pos += tmp;

	m_gravity_force = 0;
	m_height = m_threshold - 10;
	enable_gravity();
	m_angle = Pi;
}

void Missile::get_target()
{
	Object* ret = nullptr;

	MSG_DIS->dispatch_message(0.0, m_id, ID(UID_MGR_OBJ), msg::TYPE::GET_MISSILE_TARGET,this);
}



void Missile::reach_peak()
{
	switch (m_missile_type)
	{
	case MissileType::NORMAL:
		get_target();
		turnaround();
		break;
	case MissileType::RAIN:
		get_target();
		rain();
		break;
	}
}



void Missile::rain()
{
	//ターゲットがいなければそのまま落ちる
	if (m_target != nullptr)m_pos = m_target->get_p();

	for (int i = 0; i < m_duration; i += m_rain_interval)
	{					
		Circle cir = Circle(m_pos, Random(m_rain_area));
		Vec2 pos = Vec2(RandomVec2(cir));
		double strength = Random(-3.0, -2.0);
		InkballParm* ibp = new InkballParm(pos, double(m_threshold - 1000), Vec2(0.0, 0.0), strength, m_color, 0.5);
		MSG_DIS->dispatch_message(double(i), m_id, UID_MGR_OBJ, msg::TYPE::CREATE_INK_BALL, ibp,true,true);
	}

	//自身は空中爆発
	destroy();
}			