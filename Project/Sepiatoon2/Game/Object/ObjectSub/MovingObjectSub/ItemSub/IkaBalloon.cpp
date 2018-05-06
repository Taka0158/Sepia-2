#include"IkaBalloon.h"

IkaBalloon::IkaBalloon(Map* _map,Vec2 _init_pos, IkaBalloonType _type) :Item(ID(ID_OBJ_IKA_BALLOON))
{
	m_map = _map;
	m_pos = _init_pos;
	m_type = _type;

	set_id();
	initialize();
	init_moving_param();
	set_moving_parm();
}

IkaBalloon::~IkaBalloon()
{

}

void IkaBalloon::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = 1;
	m_init_depth = 1;
	m_mask_radius = 28.0;
	m_mask_height = 48.0;
}

void IkaBalloon::finalize()
{

}

void IkaBalloon::update()
{
	m_timer++;
	gravity();
	behavior_update();

	mask_update();

	restrain();
}

void IkaBalloon::draw()
{
	draw_shadow(1.0,Vec2(0.0,48.0),0);
	get_tex()->scale(1.0).drawAt(get_pos_height());
}

void IkaBalloon::debug_update()
{

}

void IkaBalloon::debug_draw()
{
	m_mask.drawFrame(1.0, 0.0, Palette::Red);
}

void IkaBalloon::set_id()
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
void IkaBalloon::init_id()
{
	m_next_valid_id = 0;
}

bool IkaBalloon::handle_message(const Telegram& _msg)
{
	//NONE
	return true;
}

bool IkaBalloon::handle_collide(CollidableObject* _obj)
{
	on_collide(_obj);
	return true;
}

bool IkaBalloon::on_collide(CollidableObject* _obj)
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		m_color=other->get_color();
		explode();
		ret = true;
	}
	else if (Inkball* other = dynamic_cast<Inkball*>(_obj))
	{
		m_color = other->get_color();
		explode();
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

void IkaBalloon::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void IkaBalloon::behavior_update()
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


void IkaBalloon::restrain()
{
	Size s = m_map->get_map_size();

	//マップ外に出ると破壊
	if (m_pos.x < 0 || s.x < m_pos.x)destroy();
	if (m_pos.y < 0 || s.y < m_pos.y)destroy();

}
void IkaBalloon::destroy()
{
	m_is_alive = false;
}

Texture* IkaBalloon::get_tex()
{
	Texture* ret=nullptr;

	switch (m_type)
	{
	case IkaBalloonType::ITEM:
		ret = &ASSET_FAC->get_tex(ImageType::IKA_BALLOON_1);
		break;
	case IkaBalloonType::ORB:
		ret = &ASSET_FAC->get_tex(ImageType::IKA_BALLOON_2);
		break;
	}
	return ret;
}

void IkaBalloon::explode()
{
	if (m_type == IkaBalloonType::ITEM)
	{
		int p = Random(0, ENUM_NUM_ITEM_TYPE - 1);
		execute_item(ItemType(p));
	}
	else if(m_type==IkaBalloonType::ORB)
	{
		int num_of_orb = Random(2, 6);
		for (int i = 0; i < num_of_orb; i++)
		{
			OrbParm* op=new OrbParm(m_pos,100,RandomVec2(Random(-2.0,2.0),Random(-2.0,2.0)),Random(3.0,4.0));
			MSG_DIS->dispatch_message(i * 100, m_id, ID(UID_MGR_OBJ), msg::TYPE::CREATE_ORB, op, false, true);
		}
	}
	destroy();
}

void IkaBalloon::execute_item(ItemType _type)
{
	if (_type == ItemType::MULTI_MISSILE)
	{
		int num_of_missile = Random(3, 6);
		for (int i = 0; i < num_of_missile; i++)
		{
			MissileParm *mp = new MissileParm(m_pos, 25, m_color, true,MissileType::NORMAL);
			MSG_DIS->dispatch_message(i * 60, m_id, ID(UID_MGR_OBJ), msg::TYPE::CREATE_MISSILE, mp, false, true);
		}
	}
	else if (_type == ItemType::RAIN)
	{
		MissileParm *mp = new MissileParm(m_pos, 25, m_color, true, MissileType::RAIN);
		MSG_DIS->dispatch_message(0, m_id, ID(UID_MGR_OBJ), msg::TYPE::CREATE_MISSILE, mp, false, true);
	}
	else  if (_type == ItemType::RUMBA)
	{
		RumbaParm* rp = new RumbaParm(m_pos, m_color);
		MSG_DIS->dispatch_message(0.0, m_id, ID(UID_MGR_OBJ), msg::TYPE::CREATE_RUMBA, rp, false, true);
	}
}