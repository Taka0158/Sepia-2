#include"IkaSwim.h"

class IkaNormal;
class IkaSink;


IkaSwim::IkaSwim():IkaState(IkaStateType::IKA_SWIM)
{

}

IkaSwim::~IkaSwim()
{

}

void IkaSwim::enter(Ika* _owner)
{
	_owner->set_moving_parm(m_state_type);
	_owner->paint();
}

void IkaSwim::update(Ika* _owner)
{
	_owner->behavior_update();

	state(_owner);

	input(_owner);

	//State遷移処理
	execute_change_state(_owner);
}

void IkaSwim::draw(Ika* _owner)
{
	Println(L"IkaSwim");
	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	_owner->get_tex_s().scale(scale).rotate(angle).drawAt(_owner->get_p(), _owner->get_color());
}

void IkaSwim::exit(Ika* _owner)
{

}

void IkaSwim::input(Ika* _owner)
{
	IkaController* controller = _owner->get_controller();
	if (!controller->is_pressed_swim())
	{
		set_next_state(IkaStateType::IKA_NORMAL);
	}
}

void IkaSwim::state(Ika* _owner)
{
	int ground_color = check_ground_color(_owner);
	if (ground_color==COLOR_NEUTRAL)
	{
		set_next_state(IkaStateType::IKA_NORMAL);
	}
	else if (ground_color == COLOR_RIVAL)
	{
		set_next_state(IkaStateType::IKA_SINK);
	}
}

bool IkaSwim::on_collide(Ika* _owner, Object* _obj)
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
			else
			{
				_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*2.0);
			}
			break;
		case IST::IKA_SWIM:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*2.0);
			//互いに影響なし
			break;
		case IST::IKA_SINK:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*2.0);
			//影響なし
			break;
		}
	}

	return ret;
}