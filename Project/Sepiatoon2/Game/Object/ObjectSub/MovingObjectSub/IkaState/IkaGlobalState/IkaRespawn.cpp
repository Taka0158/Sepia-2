#include"IkaRespawn.h"

IkaRespawn::IkaRespawn() :IkaState(IkaStateType::IKA_RESPAWN)
{

}

IkaRespawn::~IkaRespawn()
{

}

void IkaRespawn::enter(Ika* _owner)
{
	_owner->set_moving_parm(m_state_type);
}

void IkaRespawn::update(Ika* _owner)
{

}

void IkaRespawn::draw(Ika* _owner)
{
	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	_owner->get_tex_n().scale(scale).rotate(angle).drawAt(_owner->get_pos_height(), Color(_owner->get_color(), 150));
}

void IkaRespawn::exit(Ika* _owner)
{

}

