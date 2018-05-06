#include"IkaDamaged.h"


IkaDamaged::IkaDamaged() :IkaState(IkaStateType::IKA_DAMAGED)
{

}

IkaDamaged::~IkaDamaged()
{

}

void IkaDamaged::enter(Ika* _owner)
{
	m_timer = 0;
	_owner->set_moving_parm(m_state_type);
	
	//遅延メッセージだと受け取り損なうと変化できない
	//MSG_DIS->dispatch_message(m_invincible_time*MSG_SEC, _owner, _owner, msg::TYPE::DELETE_IKA_GLOBAL_STATE);

}

void IkaDamaged::update(Ika* _owner)
{
	m_timer++;

	_owner->behavior_update();

	state(_owner);
}

void IkaDamaged::draw(Ika* _owner)
{
	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	_owner->get_tex_c().scale(scale).rotate(angle).drawAt(_owner->get_pos_height(), Color(_owner->get_color(), 100));
}

void IkaDamaged::exit(Ika* _owner)
{

}

void IkaDamaged::state(Ika* _owner)
{
	if (m_timer > m_invincible_time)
	{
		MSG_DIS->dispatch_message(0.0, _owner, _owner, msg::TYPE::DELETE_IKA_GLOBAL_STATE);
	}
}