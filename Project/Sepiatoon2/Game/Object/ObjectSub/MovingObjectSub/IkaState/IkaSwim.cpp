#include"IkaSwim.h"

class IkaNormal;
class IkaSink;

//TODO
#include"IkaSink.h"

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

	//State‘JˆÚˆ—
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
	if (!controller->get_key_swim().pressed)
	{
		set_next_state(new IkaNormal());
	}
}

void IkaSwim::state(Ika* _owner)
{
	int ground_color = check_ground_color(_owner);
	if (ground_color==COLOR_NEUTRAL)
	{
		set_next_state(new IkaNormal());
	}
	else if (ground_color == COLOR_RIVAL)
	{
		set_next_state(new IkaSink());
	}
}

