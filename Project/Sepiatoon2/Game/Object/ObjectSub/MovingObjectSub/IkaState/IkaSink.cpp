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

	//State‘JˆÚˆ—
	execute_change_state(_owner);
}

void IkaSink::draw(Ika* _owner)
{
	Println(L"IkaSink");
	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	_owner->get_tex_c().scale(scale).rotate(angle).drawAt(_owner->get_p(), _owner->get_color());
}

void IkaSink::exit(Ika* _owner)
{
	_owner->paint();

}

void IkaSink::input(Ika* _owner)
{
	IkaController* controller = _owner->get_controller();
	if (!controller->get_key_swim().pressed)
	{
		set_next_state(new IkaNormal());
	}
}

void IkaSink::state(Ika* _owner)
{
	if (check_ground_color(_owner) == COLOR_MINE)
	{
		set_next_state(new IkaNormal());
	}
}