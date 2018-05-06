#include"Trampoline.h"


Trampoline::Trampoline(Map* _map,Vec2 _init_pos) :MapGimmick(ID(ID_MAPGIMMICK_TRAMPOLINE))
{
	m_map = _map;
	init_moving_param();
	set_id();
	m_pos = _init_pos;
	set_moving_parm();
	initialize();
}

Trampoline::~Trampoline()
{

}

void Trampoline::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = 3;
	m_init_depth = 3;
	m_mask_radius = 50;
	mask_update();
	m_color = Color(255, 255, 255, 255);
}

void Trampoline::finalize()
{

}

void Trampoline::update()
{
	//動かないため不要
	//behavior_update();

	//動かないため不要
	//mask_update();


	restrain();
}

void Trampoline::draw()
{
	ASSET_FAC->get_tex(ImageType::TRAMPOLINE).drawAt(m_pos,m_color);
}

void Trampoline::debug_update()
{
	if (Input::KeyDelete.clicked)
	{
		m_is_alive = false;
	}
}

void Trampoline::debug_draw()
{
	m_mask.drawFrame(1.0,0.0,Palette::Red);
	FONT_DEBUG_8(to_hex(m_id)).drawCenter(m_pos, Palette::Black);
}

void Trampoline::set_id()
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
void Trampoline::init_id()
{
	m_next_valid_id = 0;
}

bool Trampoline::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool Trampoline::on_message(const Telegram& _msg)
{
	bool ret = false;

	return ret;
}

bool Trampoline::handle_collide(CollidableObject* _obj)
{
	on_collide(_obj);

	return true;
}

bool Trampoline::on_collide(CollidableObject* _obj)
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		//泳ぎ状態で触れることでswim_jumpパラメータ上昇
		if (other->get_ika_fsm()->get_current_state()->get_state_type() == IkaStateType::IKA_SWIM)
		{
			m_color = other->get_color();
			other->set_swim_jump(TRAMPOLINE_SCALING);
		}
		ret = true;
	}

	ret = true;

	return ret;
}

void Trampoline::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void Trampoline::behavior_update()
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

void Trampoline::restrain()
{
	Size s = m_map->get_map_size();

	if (m_pos.x < 0 || s.x < m_pos.x)m_velocity.x = m_velocity.x*-1;
	if (m_pos.y < 0 || s.y < m_pos.y)m_velocity.y = m_velocity.x*-1;
	
	m_pos = clamp(m_pos, Vec2(0.0, 0.0), Vec2(s));
}