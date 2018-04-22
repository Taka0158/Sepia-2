#include"IkaNormal.h"

//‘JˆÚæƒNƒ‰ƒX
class IkaSwim;
class IkaSink;

//TODO
#include"IkaSink.h"
#include"IkaSwim.h"

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

	//State‘JˆÚˆ—
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
	if (controller->get_key_swim().pressed)
	{
		if (check_ground_color(_owner)==COLOR_MINE)
		{
			set_next_state(new IkaSwim());
		}
	}
}

void IkaNormal::state(Ika* _owner)
{
	if (check_ground_color(_owner) == COLOR_RIVAL)
	{
		set_next_state(new IkaSink());
	}
}