#include"IkaSpecialSupernova.h"

IkaSpecialSupernova::IkaSpecialSupernova() :IkaState(IkaStateType::IKA_SPECIAL_SUPERNOVA)
{

}

IkaSpecialSupernova::~IkaSpecialSupernova()
{

}

void IkaSpecialSupernova::state(Ika* _owner)
{

}
void IkaSpecialSupernova::enter(Ika* _owner)
{
	_owner->set_moving_parm(m_state_type);

}
void IkaSpecialSupernova::update(Ika* _owner)
{

}
void IkaSpecialSupernova::draw(Ika* _owner)
{
	Println(L"IkaSpecialDash");

}
void IkaSpecialSupernova::exit(Ika* _owner)
{

}