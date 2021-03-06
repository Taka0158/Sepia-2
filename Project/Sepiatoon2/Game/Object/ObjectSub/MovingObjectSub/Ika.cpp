#include"Ika.h"

Ika::Ika(Map* _map, ControllerType _controller_type,Vec2 _init_p, Color _color, TeamType _team_type, CharType _char_type, SpecialType _special_type):MovingObject(ID(ID_OBJ_IKA))
{
	set_id();
	set_char_param(_char_type);

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

	//イカを被写体に追加
	MSG_DIS->dispatch_message(0, m_id, UID_SCENE_CAMERA, msg::TYPE::REGIST_CAMERA_SUBJECT, this);

}
Ika::~Ika()
{
	finalize();
	//イカを被写体から削除
	MSG_DIS->dispatch_message(0, m_id, UID_SCENE_CAMERA, msg::TYPE::RESET_CAMERA_SUBJECT, this);
}

void Ika::initialize()
{
	finalize();

	m_is_alive = true;
	m_pos = m_init_pos;
	m_target_pos = Vec2(0.0, 0.0);

	m_depth = 0;
	m_angle = 0.0;
	m_height = 50.0;

	m_mask_radius = 32.0;
}

void Ika::finalize()
{
	m_is_alive = false;

	//m_ika_fsm.release();
}

void Ika::update()
{
	//コリジョンマスクの座標更新
	mask_update();

	m_ika_fsm->update();

	restrain();

	//この関数はState内で適宜呼ばれたり、よばれなかったり
	//behavior_update();

	calc_angle(m_angle);

	gravity();

	if (m_hp < 0.0)
	{
		m_is_alive = false;
		finalize();
	}
}

void Ika::draw()
{
	draw_shadow();
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
	Color c1 = Setting::get_color(TeamType::TEAM_A);
	Color c2 = Setting::get_color(TeamType::TEAM_B);
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
	if (Input::KeyQ.clicked)
	{
		execute_special();
	 }
}

void Ika::debug_draw()
{
	m_mask.drawFrame(1.0,0.0,Palette::Red);
	FONT_DEBUG_8(L"HP:", m_hp).drawCenter(get_p(),Palette::Black);
	FONT_DEBUG_8(L"GAUGE:", m_special_gauge).drawCenter(Vec2(get_p().x, get_p().y + 8.0), Palette::Black);
	FONT_DEBUG_8(L"depth:", m_depth).drawCenter(Vec2(get_p().x, get_p().y + 16.0), Palette::Black);
	FONT_DEBUG_8(L"height:", m_height).drawCenter(Vec2(get_p().x, get_p().y + 24.0), Palette::Black);
	//Println(L"m_velocity", m_velocity);
	//Println(L"m_heading", m_heading);
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

void Ika::init_id()
{
	m_next_valid_id = 0;
}

void Ika::set_moving_parm()
{
	switch (m_char_type)
	{
	case CharType::NORMAL:
		//適当パラメータ
		m_init_mass = 1.0;
		m_init_max_speed = 6.0;
		m_init_max_force = 10.0;
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
	case IkaStateType::IKA_SPECIAL_TYPHOON:
	case IkaStateType::IKA_SPECIAL_DASH:
	case IkaStateType::IKA_SPECIAL_SUPERNOVA:
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
	if(m_height<=0.2)m_velocity -= m_velocity*m_friction;

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

	Paint p = Paint(pos, m_color,m_paint_scale);

	MSG_DIS->dispatch_message(0.0, m_id, m_map->get_id(), msg::TYPE::MAP_PAINT, &p,false);

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
		ret = true;
		break;
	case msg::TYPE::SET_IKA_GLOBAL_STATE:
		new_state_type = (IkaStateType*)_msg.extraInfo;
		set_global_state(*new_state_type);
		ret = true;
		break;
	case msg::TYPE::DELETE_IKA_GLOBAL_STATE:
		m_ika_fsm->delete_global_state();
		ret = true;
		break;
	case msg::TYPE::EXECUTE_IKA_SPECIAL:
		execute_special();
		ret = true;
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

void Ika::damaged(double _damage)
{
	//スペシャル中ならダメージを受けない
	if (m_ika_fsm->get_global_state() != nullptr)
	{
		if (m_ika_fsm->get_global_state()->get_state_type() == IkaStateType::IKA_SPECIAL_TYPHOON)return;
		else if (m_ika_fsm->get_global_state()->get_state_type() == IkaStateType::IKA_SPECIAL_SUPERNOVA)return;
		else if (m_ika_fsm->get_global_state()->get_state_type() == IkaStateType::IKA_SPECIAL_DASH)return;
	}
	m_hp -= _damage;
	overwrite_global_state(IkaStateType::IKA_DAMAGED);
}

//相手タイプにより被ダメ増減
void Ika::damaged(CharType _type)
{
	switch (_type)
	{
	case CharType::NORMAL:
		damaged(30.0);
		break;
	}
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

	typedef IkaStateType IST;
	//タイヤとの接触なら
	if (is_same_class(_obj->get_id(), ID_MAPGIMMCIK_TIRE))
	{
		if ( !(m_ika_fsm->get_now_state()== IST::IKA_SPECIAL_TYPHOON))
		{
			burst(get_Vec2(_obj->get_p(), m_pos)*5.0);
		}
	}
	else
	{
		//FSMに丸投げ
		ret = m_ika_fsm->on_collide(_obj);
	}

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
	//上書きは行われない
	switch (_type)
	{
	case IkaStateType::IKA_DAMAGED:
		m_ika_fsm->set_global_state(new IkaDamaged());
		break;
	case IkaStateType::IKA_SPECIAL_TYPHOON:
		m_ika_fsm->set_global_state(new IkaSpecialTyphoon());
		break;
	case IkaStateType::IKA_SPECIAL_DASH:
		m_ika_fsm->set_global_state(new IkaSpecialDash());
		break;
	case IkaStateType::IKA_SPECIAL_SUPERNOVA:
		m_ika_fsm->set_global_state(new IkaSpecialSupernova());
		break;
	}
}

void Ika::overwrite_global_state(IkaStateType _type)
{
	switch (_type)
	{
	case IkaStateType::IKA_DAMAGED:
		m_ika_fsm->overwrite_global_state(new IkaDamaged());
		break;
	default:
		ASSERT(L"global_staetに上書き出来ないIkaStateTypeです");
		break;
	}
}

void Ika::execute_special()
{
	MSG_DIS->dispatch_message(0.0, this->m_id, UID_MGR_SCENE, msg::TYPE::SET_CUTIN, this);
	switch (m_special_type)
	{
	case SpecialType::DASH:
		set_global_state(IkaStateType::IKA_SPECIAL_DASH);
		break;
	case SpecialType::TYPHOON:
		set_global_state(IkaStateType::IKA_SPECIAL_TYPHOON);
		break;
	case SpecialType::SUPERNOVA:
		set_global_state(IkaStateType::IKA_SPECIAL_SUPERNOVA);
		break;
	}

}

void Ika::set_char_param(CharType _type)
{
	typedef CharType CT;
	switch (_type)
	{
		//TODO
	case CT::NORMAL:
		m_init_hp = 100.0;
		m_init_special_gauge = 0.0;
		m_init_paint_scale = 1.0;
		m_init_gauge_rate = 1.0;
		m_init_mask_radius = 32.0;
		m_init_mask_height = 2.0;
		break;
	}
	init_param();
}

void Ika::init_param()
{
	m_hp = m_init_hp;
	m_special_gauge = m_init_special_gauge;
	m_paint_scale = m_init_paint_scale;
	m_gauge_rate = m_init_gauge_rate;
	m_mask_radius = m_init_mask_radius;
	m_mask_height = m_init_mask_height;
}

