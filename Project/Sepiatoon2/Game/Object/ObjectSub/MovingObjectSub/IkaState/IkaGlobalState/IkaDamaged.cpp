#include"IkaDamaged.h"

//‘JˆÚæƒNƒ‰ƒX
class IkaNorml;

//TODO
#include"../IkaNormal.h"

IkaDamaged::IkaDamaged() :IkaState(IkaStateType::IKA_DAMAGED)
{

}

IkaDamaged::~IkaDamaged()
{

}

void IkaDamaged::enter(Ika* _owner)
{
	_owner->set_moving_parm(m_state_type);
	MSG_DIS->dispatch_message(m_invincible_time*MSG_SEC, _owner, _owner, msg::TYPE::DELETE_IKA_GLOBAL_STATE);
}

void IkaDamaged::update(Ika* _owner)
{
	_owner->behavior_update();

	state(_owner);

}

void IkaDamaged::draw(Ika* _owner)
{
	Println(L"IkaDamaged");
	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	_owner->get_tex_c().scale(scale).rotate(angle).drawAt(_owner->get_p(), Color(_owner->get_color(), 100));
}

void IkaDamaged::exit(Ika* _owner)
{

}

void IkaDamaged::state(Ika* _owner)
{

}