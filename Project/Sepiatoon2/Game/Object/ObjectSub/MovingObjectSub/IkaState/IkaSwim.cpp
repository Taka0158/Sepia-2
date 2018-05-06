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
	_owner->set_init_depth(-100);
}

void IkaSwim::update(Ika* _owner)
{
	_owner->behavior_update();

	state(_owner);

	input(_owner);

	_owner->regene_hp();

	//State�J�ڏ���
	execute_change_state(_owner);

}

void IkaSwim::draw(Ika* _owner)
{
	Println(L"IkaSwim");
	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	_owner->get_tex_s().scale(scale).rotate(angle).drawAt(_owner->get_pos_height(), _owner->get_color());
}

void IkaSwim::exit(Ika* _owner)
{
	_owner->set_init_depth(0);

	//�C���N����o��Ƃ��ɂ̓W�����v���ăC���N�{�[������
	_owner->fly(_owner->get_swim_jump());
	_owner->init_swim_jump();

	InkballParm ibp = InkballParm(_owner->get_p(), _owner->get_height() + 5.0, _owner->get_heading()*_owner->get_velocity().length(), _owner->get_velocity().length()*0.20, _owner->get_color());
	MSG_DIS->dispatch_message(0.0, _owner->get_id(), UID_MGR_OBJ, msg::TYPE::CREATE_INK_BALL, &ibp,false);
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
	//�����Ă�����
	if (_owner->get_height() >= ON_GROUND_THRESHOLD)
	{
		set_next_state(IkaStateType::IKA_NORMAL);
	}
	else
	{
		if (ground_color == COLOR_NEUTRAL)
		{
			set_next_state(IkaStateType::IKA_NORMAL);
		}
		else if (ground_color == COLOR_RIVAL)
		{
			set_next_state(IkaStateType::IKA_SINK);
		}
	}

}

bool IkaSwim::on_collide(Ika* _owner, CollidableObject* _obj)
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
			//�݂��ɉe���Ȃ�
			break;
		case IST::IKA_SINK:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*2.0);
			//�e���Ȃ�
			break;
		case IST::IKA_SPECIAL_TYPHOON:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*10.0);
			_owner->damaged(IKA_TYPHOON_DAMAEG);
			break;
		case IST::IKA_SPECIAL_SUPERNOVA:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*10.0);
			_owner->damaged(IKA_SUPERNOVA_DAMAEG);
			break;
		case IST::IKA_SPECIAL_DASH:
			_owner->burst(get_Vec2(other->get_p(), _owner->get_p())*10.0);
			_owner->damaged(IKA_DASH_DAMAGE);
			break;
		}
	}

	return ret;
}