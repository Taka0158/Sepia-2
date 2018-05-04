#include"IkaSink.h"

class IkaNormal;

IkaSink::IkaSink() :IkaState(IkaStateType::IKA_SINK)
{

}

IkaSink::~IkaSink()
{

}

void IkaSink::enter(Ika* _owner)
{
	_owner->set_moving_parm(m_state_type);
}

void IkaSink::update(Ika* _owner)
{
	_owner->behavior_update();

	state(_owner);

	input(_owner);

	//State遷移処理
	execute_change_state(_owner);

	
}

void IkaSink::draw(Ika* _owner)
{
	Println(L"IkaSink");
	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	_owner->get_tex_c().scale(scale).rotate(angle).drawAt(_owner->get_pos_height(), _owner->get_color());
}

void IkaSink::exit(Ika* _owner)
{
	_owner->paint();

}

void IkaSink::input(Ika* _owner)
{
	IkaController* controller = _owner->get_controller();
	if (!controller->is_pressed_swim())
	{
		set_next_state(IkaStateType::IKA_NORMAL);
	}
}

void IkaSink::state(Ika* _owner)
{
	if (check_ground_color(_owner) == COLOR_MINE )
	{
		set_next_state(IkaStateType::IKA_NORMAL);
	}
}

bool IkaSink::on_collide(Ika* _owner, CollidableObject* _obj)
{
	bool ret = false;

	//相手がイカクラスなら
	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		typedef IkaStateType IST;
		//相手のステイトに応じて処理
		switch (other->get_ika_fsm()->get_now_state())
		{
		case IST::IKA_NORMAL:
			if (other->get_team_type() != _owner->get_team_type())
			{
				MSG_DIS->dispatch_message(0.0, _owner->get_id(), UID_SCENE_CAMERA, msg::TYPE::SHAKE_CAMERA, &get_Vec2(other->get_p(), _owner->get_p()));
				_owner->damaged(other->get_char_type());
				_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*3.0);
			}
			break;
		case IST::IKA_SWIM:
			if (other->get_team_type() != _owner->get_team_type())
			{
				MSG_DIS->dispatch_message(0.0, _owner->get_id(), UID_SCENE_CAMERA, msg::TYPE::SHAKE_CAMERA, &get_Vec2(other->get_p(), _owner->get_p()));
				_owner->damaged(other->get_char_type());
				_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*3.0);
			}
			break;
		case IST::IKA_SINK:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*2.0);
			//互いに影響なし
			break;
		case IST::IKA_SPECIAL_TYPHOON:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*10.0);
			_owner->damaged(IKA_TYPHOON_DAMAEG);
			break;
		case IST::IKA_SPECIAL_SUPERNOVA:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*10.0);
			_owner->damaged(IKA_SUPERNOVA_DAMAEG);
			break;
		}


	}

	return ret;
}