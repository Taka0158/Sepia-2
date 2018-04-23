#include"Ika.h"

Ika::Ika(Map* _map, ControllerType _controller_type,Vec2 _init_p, Color _color, TeamType _team_type, CharType _char_type, SpecialType _special_type):MovingObject(ID(ID_OBJ_IKA))
{
	m_map = _map;
	m_color = _color;
	m_team_type = _team_type;
	m_char_type = _char_type;
	m_special_type = _special_type;
	m_controller_type = _controller_type;

	regist_texture(m_char_type);
	regist_controller(m_controller_type);
	set_moving_parm();
	set_rival_color();

	set_init_pos(_init_p);
	initialize();

	m_ika_fsm.reset(new IkaStateMachine(this));
	m_ika_fsm->set_current_state(new IkaNormal());
	m_ika_fsm->set_global_state(nullptr);

}
Ika::~Ika()
{
	finalize();
}

void Ika::initialize()
{
	finalize();

	m_is_alive = true;
	m_pos = m_init_pos;
	m_target_pos = Vec2(0.0, 0.0);

	m_depth = 5;
	m_angle = 0.0;

	m_mask_radius = 32.0;
}

void Ika::finalize()
{
	m_is_alive = false;

	m_ika_fsm.release();
}

void Ika::update()
{
	//コリジョンマスクの座標更新
	mask_update();

	m_ika_fsm->update();

	restrain();

	//この関数はState内で適宜呼ばれたり、よばれなかったり
	//behavior_update();

	calc_angle();
}

void Ika::draw()
{
	m_ika_fsm->draw();
}

void Ika::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}

void Ika::regist_texture(CharType _type)
{
	switch (_type)
	{
	case CharType::NORMAL:
		m_tex_a = ASSET_FAC->get_tex(ImageType::IKA_N_A);
		m_tex_c = ASSET_FAC->get_tex(ImageType::IKA_N_C);
		m_tex_n = ASSET_FAC->get_tex(ImageType::IKA_N_N);
		m_tex_s = ASSET_FAC->get_tex(ImageType::IKA_N_S);
		break;
	}
}

void Ika::set_rival_color()
{
	Color c1 = Setting::get_color_A();
	Color c2 = Setting::get_color_B();
	if (m_color == c1)
	{
		m_rival_color = c2;
	}
	else
	{
		m_rival_color = c1;
	}
}

void Ika::regist_controller(ControllerType _c_type)
{
	switch (_c_type)
	{
	case ControllerType::PLAYER_1:
	case ControllerType::PLAYER_2:
		m_controller.reset(new IkaPlayerController(this));
		break;
	case ControllerType::CPU:
		m_controller.reset(new IkaAIController(this));
		break;
	}
}

void Ika::debug_update()
{

}

void Ika::debug_draw()
{
	m_mask.drawFrame(1.0,0.0,Palette::Red);
	FONT_DEBUG_8(L"HP:", m_hp).drawCenter(get_p());
	Println(L"m_velocity", m_velocity);
	Println(L"m_heading", m_heading);
}

void Ika::set_id()
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

void Ika::set_moving_parm()
{
	switch (m_char_type)
	{
	case CharType::NORMAL:
		//適当パラメータ
		m_init_mass = 1.0;
		m_init_max_speed = 6.0;
		m_init_max_force = 5.0;
		m_init_max_turn_rate = 0.02;
		m_init_friction = 0.05;
		break;
	}
	set_moving_parm(m_init_mass, m_init_max_speed, m_init_max_force, m_init_max_turn_rate, m_init_friction);
}

void Ika::set_moving_parm(double _mass,double _max_speed,double _max_force,double _max_turn_rate,double _friction)
{
	m_mass = _mass;
	m_max_speed = _max_speed;
	m_max_force = _max_force;
	m_max_turn_rate = _max_turn_rate;
	m_friction = _friction;
}

void Ika::set_moving_parm(IkaStateType _type)
{
	switch (_type)
	{
	case IkaStateType::IKA_NORMAL:
		set_moving_parm(m_init_mass, m_init_max_speed, m_init_max_force, m_init_max_turn_rate, m_init_friction);
		break;
	case IkaStateType::IKA_SWIM:
		set_moving_parm(m_init_mass, m_init_max_speed*1.5, m_init_max_force, m_init_max_turn_rate, m_init_friction*0.5);
		break;
	case IkaStateType::IKA_SINK:
		set_moving_parm(m_init_mass, m_init_max_speed*0.5, m_init_max_force, m_init_max_turn_rate, m_init_friction);
		break;
	case IkaStateType::IKA_DAMAGED:
	case IkaStateType::IKA_SPECIAL:
		set_moving_parm(m_init_mass, m_init_max_speed, m_init_max_force, m_init_max_turn_rate, m_init_friction);
		break;
	}
}

void Ika::behavior_update()
{
	//前の座標を保持
	Vec2 old_pos = m_pos;

	Vec2 steering_force;

	//移動する方向への力を入力(AI:計算)する
	steering_force = m_controller->calculate(this);

	//加速度の算出
	Vec2 acceleration = steering_force / m_mass;

	//速度の加算
	m_velocity += acceleration;

	//摩擦による速度の減算
	m_velocity -= m_velocity*m_friction;

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

void Ika::paint()
{
	Point pos = Vec2_to_Point(m_pos);

	//if (m_map->get_color(pos) != m_rival_color)return;

	Paint p = Paint(pos, m_color);

	MSG_DIS->dispatch_message(0.0, m_id, m_map->get_id(), msg::TYPE::MAP_PAINT, &p);

}

bool Ika::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool Ika::on_message(const Telegram& _msg)
{
	bool ret = false;
	IkaStateType* new_state_type;

	switch (_msg.msg)
	{
	case msg::TYPE::CHANGE_IKA_STATE:
		new_state_type = (IkaStateType*)_msg.extraInfo;
		set_state(*new_state_type);
		break;
	case msg::TYPE::SET_IKA_GLOBAL_STATE:
		new_state_type = (IkaStateType*)_msg.extraInfo;
		set_global_state(*new_state_type);
		break;
	case msg::TYPE::DELETE_IKA_GLOBAL_STATE:
		m_ika_fsm->delete_global_state();
		break;
	}

	return ret;
}

void Ika::restrain()
{
	//マップの左上座標
	Vec2 p1 = m_map->get_p();
	Vec2 p2 = m_map->get_map_size();

	m_pos = clamp(m_pos, p1, p2);
}

void Ika::calc_angle()
{
	//前作からのコピペ
	//角度計算
	if (m_velocity.length() <= m_max_speed*0.2)return;
	double angletemp = Atan2(m_velocity.y, m_velocity.x);
	//回転角の小さい方をdiffとする（この部分）
	double anglediff1 = (abs(angletemp - m_angle)<Pi) ? angletemp - m_angle : 2 * Pi - abs(angletemp - m_angle);
	double angle_add = Pi / 180 * 3 ;
	double temp = Sign(anglediff1)*angle_add;
	m_angle += temp;
	if (m_angle > 2 * Pi)m_angle -= 2 * Pi;
	else if (m_angle < -Pi + 1)m_angle += 2 * Pi;
}

void Ika::damaged(double _damage)
{
	m_hp -= _damage;
	set_global_state(IkaStateType::IKA_DAMAGED);
}

void Ika::damaged(CharType _type)
{
	switch (_type)
	{
	case CharType::NORMAL:
		damaged(30.0);
		break;
	}
}

void Ika::burst(Vec2 _power)
{
	m_velocity = _power;
}

void Ika::destroy()
{
	finalize();
}

bool Ika::handle_collide(Object* _obj)
{
	on_collide(_obj);
	return true;
}

bool Ika::on_collide(Object* _obj)
{
	bool ret = false;

	//FSMに丸投げ
	ret = m_ika_fsm->on_collide(_obj);

	return ret;
}

void Ika::set_state(IkaStateType _type)
{
	switch (_type)
	{
	case IkaStateType::IKA_NORMAL:
		m_ika_fsm->change_state(new IkaNormal());
		break;
	case IkaStateType::IKA_SINK:
		m_ika_fsm->change_state(new IkaSink());
		break;
	case IkaStateType::IKA_SWIM:
		m_ika_fsm->change_state(new IkaSwim());
		break;
	}
}

void Ika::set_global_state(IkaStateType _type)
{
	switch (_type)
	{
	case IkaStateType::IKA_DAMAGED:
		m_ika_fsm->set_global_state(new IkaDamaged());
		break;
	case IkaStateType::IKA_SPECIAL:
		//未実装
		//m_ika_fsm->set_global_state(new IkaSpecial());
		break;
	}
}