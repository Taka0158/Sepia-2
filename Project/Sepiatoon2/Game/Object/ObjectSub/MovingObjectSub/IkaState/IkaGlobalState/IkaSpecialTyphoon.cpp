#include"IkaSpecialTyphoon.h"

IkaSpecialTyphoon::IkaSpecialTyphoon() :IkaState(IkaStateType::IKA_SPECIAL_TYPHOON)
{

}

IkaSpecialTyphoon::~IkaSpecialTyphoon()
{

}

void IkaSpecialTyphoon::state(Ika* _owner)
{

}
void IkaSpecialTyphoon::enter(Ika* _owner)
{
	_owner->set_moving_parm(m_state_type);

}
void IkaSpecialTyphoon::update(Ika* _owner)
{

}
void IkaSpecialTyphoon::draw(Ika* _owner)
{
	Println(L"IkaSpecialDash");

}
void IkaSpecialTyphoon::exit(Ika* _owner)
{

}