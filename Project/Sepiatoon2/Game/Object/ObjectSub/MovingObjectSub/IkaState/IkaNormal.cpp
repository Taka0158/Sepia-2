#include"IkaNormal.h"

//�J�ڐ�N���X
class IkaSwim;
class IkaSink;

//TODO
#include"../IkaStateMachine.h"

IkaNormal::IkaNormal():IkaState(IkaStateType::IKA_NORMAL)
{

}

IkaNormal::~IkaNormal()
{

}

void IkaNormal::enter(Ika* _owner)
{
	_owner->set_moving_parm(m_state_type);
	old_pos_update(_owner);
}

void IkaNormal::update(Ika* _owner)
{

	_owner->behavior_update();

	paint(_owner);

	state(_owner);

	input(_owner);

	//State�J�ڏ���
	execute_change_state(_owner);
}

void IkaNormal::draw(Ika* _owner)
{
	Println(L"IkaNormal");
	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	_owner->get_tex_n().scale(scale).rotate(angle).drawAt(_owner->get_p(), _owner->get_color());
}

void IkaNormal::exit(Ika* _owner)
{

}

void IkaNormal::input(Ika* _owner)
{		
	IkaController* controller = _owner->get_controller();
	if (controller->is_pressed_swim())
	{
		if (check_ground_color(_owner)==COLOR_MINE)
		{
			set_next_state(IkaStateType::IKA_SWIM);
		}
	}
}

void IkaNormal::state(Ika* _owner)
{
	if (check_ground_color(_owner) == COLOR_RIVAL)
	{
		set_next_state(IkaStateType::IKA_SINK);
	}
}

bool IkaNormal::on_collide(Ika* _owner, Object* _obj)
{
	bool ret = false;

	//���肪�C�J�N���X�Ȃ�
	if (Ika* other = dynamic_cast<Ika*>(_obj))
	{
		typedef IkaStateType IST;
		//����̃X�e�C�g�ɉ����ď���
		switch (other->get_ika_fsm()->get_now_state())
		{
		case IST::IKA_NORMAL:
			//�قȂ�`�[���Ȃ�
			if (other->get_team_type() != _owner->get_team_type())
			{
				//����̂ق����������x�Ȃ�
				if (other->get_velocity().length() > _owner->get_velocity().length())
				{
					MSG_DIS->dispatch_message(0.0, _owner->get_id(), UID_SCENE_CAMERA, msg::TYPE::SHAKE_CAMERA, &get_Vec2(other->get_p(), _owner->get_p()));
					_owner->damaged(other->get_char_type());
					_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*3.0);
				}
				else
				{
					_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*1.5);
				}
			}
			else
			{
				_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*1.5);
			}
			break;
		case IST::IKA_SWIM:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*1.0);
			//�����ɂ͉e���Ȃ�
			break;
		case IST::IKA_SINK:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*1.0);
			//�����ɂ͉e���Ȃ�
			break;
		}
	}

	return ret;
}

/*
//�����N���X�Ƃ̏Փ�
if (is_same_class(_obj->get_id(), get_id()))
{
Ika* ika = dynamic_cast<Ika*>(_obj);
//�قȂ�`�[���Ȃ�
if(ika->get_team_type()!=get_team_type())
{
//����̂ق����������
if (ika->get_velocity().length() - get_velocity().length() >= VELOCITY_THRESHOLD)
{
damaged(ika->get_char_type());
burst(get_Vec2(ika->get_p(), get_p())*3.0);
}
}
else
{
burst(get_Vec2(ika->get_p(), get_p())*1.5);
}
ret = true;
}

*/