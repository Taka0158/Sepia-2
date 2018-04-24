#include"IkaSpecialDash.h"

IkaSpecialDash::IkaSpecialDash() :IkaState(IkaStateType::IKA_SPECIAL_DASH)
{

}

IkaSpecialDash::~IkaSpecialDash()
{

}

void IkaSpecialDash::state(Ika* _owner)
{

}
void IkaSpecialDash::enter(Ika* _owner)
{
	_owner->set_moving_parm(m_state_type);

}
void IkaSpecialDash::update(Ika* _owner)
{

}
void IkaSpecialDash::draw(Ika* _owner)
{
	Println(L"IkaSpecialDash");

}
void IkaSpecialDash::exit(Ika* _owner)
{

}