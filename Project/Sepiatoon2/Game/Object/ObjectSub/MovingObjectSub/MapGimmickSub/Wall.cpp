#include"Wall.h"


Wall::Wall(Map* _map,Vec2 _init_pos) :MapGimmick(ID(ID_MAPGIMMCIK_WALL))
{
	m_map = _map;
	init_moving_param();
	set_id();
	m_pos = _init_pos;
	set_moving_parm();
	initialize();
}

Wall::~Wall()
{

}

void Wall::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = -1;
	m_init_depth = -1;
	m_mask_radius = 63.5;
	mask_update();
}

void Wall::finalize()
{

}

void Wall::update()
{
	//動かないため不要
	//behavior_update();

	//動かないため不要
	//mask_update();

	restrain();
}

void Wall::draw()
{
	//地面に何塗られているかを分かるように乗算する
	ASSET_FAC->get_tex(ImageType::WALL).drawAt(m_pos,m_color);
}

void Wall::debug_update()
{
	if (Input::KeyDelete.clicked)
	{
		m_is_alive = false;
	}
}

void Wall::debug_draw()
{
	m_mask.drawFrame(1.0,0.0,Palette::Red);
	FONT_DEBUG_8(to_hex(m_id)).drawCenter(m_pos, Palette::Black);
}

void Wall::set_id()
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
void Wall::init_id()
{
	m_next_valid_id = 0;
}


bool Wall::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool Wall::on_message(const Telegram& _msg)
{
	bool ret = false;

	switch (_msg.msg)
	{
	case msg::TYPE::WALL_PAINT:
		Paint p= Paint(Vec2_to_Point(m_pos), Palette::Black, 1.0, &ASSET_FAC->get_image(ImageType::WALL_BLACK),false);
		MSG_DIS->dispatch_message(0.0, this, m_map, msg::TYPE::MAP_PAINT, &p);
		ret = true;
		break;
	}

	return ret;
}

bool Wall::handle_collide(CollidableObject* _obj)
{
	on_collide(_obj);

	return true;
}

bool Wall::on_collide(CollidableObject* _obj)
{
	bool ret = false;

	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{

		//泳ぐことで通過できるようにする
		if (other->get_ika_fsm()->get_current_state()->get_state_type() == IkaStateType::IKA_SWIM)
		{

		}
		else
		{
			//同じ色のいかが接触してきたら無視
			if (m_color != other->get_color())
			{
				//接触することで　壁の下を一時的に塗る
				//面積計算しないようにゲーム終了後WALL_PAINTメッセージを受け取る必要がある
				Paint p = Paint(Vec2_to_Point(m_pos), other->get_color(), 1.0, &ASSET_FAC->get_image(ImageType::WALL_BLACK),false);
				MSG_DIS->dispatch_message(0.0, this, m_map, msg::TYPE::MAP_PAINT, &p);
				m_color = other->get_color();
			}
			other->burst((other->get_p() - m_pos).normalize() * 3);
		}
		ret = true;
	}
	else if (MovingObject* other = dynamic_cast<MovingObject*>(_obj))
	{
		other->burst((other->get_p()-m_pos).normalize()*3);
		ret = true;
	}
	ret = true;

	return ret;
}

void Wall::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void Wall::behavior_update()
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

void Wall::restrain()
{
	Size s = m_map->get_map_size();

	if (m_pos.x < 0 || s.x < m_pos.x)m_velocity.x = m_velocity.x*-1;
	if (m_pos.y < 0 || s.y < m_pos.y)m_velocity.y = m_velocity.x*-1;
	
	m_pos = clamp(m_pos, Vec2(0.0, 0.0), Vec2(s));
}