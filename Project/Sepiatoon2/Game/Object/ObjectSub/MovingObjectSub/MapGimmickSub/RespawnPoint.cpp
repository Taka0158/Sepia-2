#include"RespawnPoint.h"


RespawnPoint::RespawnPoint(Map* _map,Vec2 _init_pos,Color _color) :MapGimmick(ID(ID_MAPGIMMCIK_RESPAWN_POINT))
{
	m_map = _map;
	m_color = _color;
	init_moving_param();
	set_id();
	m_pos = _init_pos;
	set_moving_parm();
	initialize();
}

RespawnPoint::~RespawnPoint()
{

}

void RespawnPoint::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = -1;
	m_init_depth = -1;
	m_mask_radius = 63.5;
	mask_update();
}

void RespawnPoint::finalize()
{

}

void RespawnPoint::update()
{
	//動かないため不要
	//behavior_update();

	//動かないため不要
	//mask_update();

	restrain();
}

void RespawnPoint::draw()
{
	//地面に何塗られているかを分かるように乗算する
	ASSET_FAC->get_tex(ImageType::RESPAWN_POINT).drawAt(m_pos,m_color);
}

void RespawnPoint::debug_update()
{
	if (Input::KeyDelete.clicked)
	{
		m_is_alive = false;
	}
}

void RespawnPoint::debug_draw()
{
	m_mask.drawFrame(1.0,0.0,Palette::Red);
	FONT_DEBUG_8(to_hex(m_id)).drawCenter(m_pos, Palette::Black);
}

void RespawnPoint::set_id()
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

void RespawnPoint::init_id()
{
	m_next_valid_id = 0;
}

bool RespawnPoint::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool RespawnPoint::on_message(const Telegram& _msg)
{
	bool ret = false;
	int ika_index;
	Paint p;

	switch (_msg.msg)
	{
	case msg::TYPE::WALL_PAINT:
		p= Paint(Vec2_to_Point(m_pos), Palette::Black, 1.0, &ASSET_FAC->get_image(ImageType::WALL_BLACK_CIRCLE),false);
		MSG_DIS->dispatch_message(0.0, this, m_map, msg::TYPE::MAP_PAINT, &p);
		ret = true;
		break;
	case msg::TYPE::RESPAWN_IKA:
		ika_index = *(int*)_msg.extraInfo;
		respawn_ika(ika_index);
		break;
	case msg::TYPE::GIVE_CREATED_IKA:
		m_created_ika = (Ika*)_msg.extraInfo;
		break;
	}

	return ret;
}

bool RespawnPoint::handle_collide(CollidableObject* _obj)
{
	on_collide(_obj);

	return true;
}

bool RespawnPoint::on_collide(CollidableObject* _obj)
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		//敵は侵入できない
		if (other->get_color() != m_color)
		{
			other->burst((other->get_p() - m_pos).normalize() * 3);
		}
	}
	else if (MovingObject* other = dynamic_cast<MovingObject*>(_obj))
	{
		other->burst((other->get_p()-m_pos).normalize()*3);
		ret = true;
	}
	ret = true;

	return ret;
}

void RespawnPoint::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void RespawnPoint::behavior_update()
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

void RespawnPoint::restrain()
{
	Size s = m_map->get_map_size();

	if (m_pos.x < 0 || s.x < m_pos.x)m_velocity.x = m_velocity.x*-1;
	if (m_pos.y < 0 || s.y < m_pos.y)m_velocity.y = m_velocity.x*-1;
	
	m_pos = clamp(m_pos, Vec2(0.0, 0.0), Vec2(s));
}

void RespawnPoint::respawn_ika(int index)
{
	//初期設定と同じ色でなければ無視
	if (m_color != Setting::get_color(index))return;

	Vec2 tmp = RandomVec2(Random(-10.0, 10.0), Random(-10.0, 10.0));
	std::pair<int, Vec2> pair = std::make_pair(index, m_pos + tmp);
	MSG_DIS->dispatch_message(0.0, m_id, ID(UID_MGR_OBJ), msg::TYPE::CREATE_IKA, &pair);

	//ここでm_created_ikaが更新

	MSG_DIS->dispatch_message(m_release_time, this, m_created_ika, msg::TYPE::DELETE_IKA_GLOBAL_STATE);
}