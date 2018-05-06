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

void IkaSpecialTyphoon::input(Ika* _owner)
{
	if (_owner->get_controller()->get_key_swim().pressed)
	{
		m_timer++;
		m_paint_scale += 0.01;
		m_mask_radius += 0.025;
		m_draw_scale += 0.0075;


	}
	else
	{

	}
}

void IkaSpecialTyphoon::enter(Ika* _owner)
{
	m_owner = _owner;

	//開始パラメータ(倍率)
	m_paint_scale = 2.5;
	m_mask_radius = 3.0;
	m_draw_scale = 2.0;

	_owner->set_special_gauge_rate(0.0);
	_owner->set_moving_parm(m_state_type);
}
void IkaSpecialTyphoon::update(Ika* _owner)
{
	input(_owner);

	_owner->set_paint_scale(m_paint_scale);
	_owner->set_mask_radius(m_mask_radius);
	
	m_is_tex_loop = (m_timer > m_duration) ? false : true;
	m_tex_index = get_tex_loop_index(m_tex_index, NUM_OF_ANIM_TYPHOON, 10, 25, m_is_tex_loop);
	m_timer++;

	//通常のstateの振る舞いをする
	_owner->get_ika_fsm()->get_current_state()->update(_owner);

	//アニメーションが最後まで再生されれば終了メッセージを送る
	if (m_tex_index >= NUM_OF_ANIM_TYPHOON - 1)
	{
		MSG_DIS->dispatch_message(0.0, _owner, _owner, msg::TYPE::DELETE_IKA_GLOBAL_STATE);
	}

}
void IkaSpecialTyphoon::draw(Ika* _owner)
{
	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	ASSET_FAC->get_tex(ImageType::ANIM_TYPHOON, m_tex_index).scale(m_draw_scale).drawAt(_owner->get_p(), _owner->get_color());
	_owner->get_ika_fsm()->get_current_state()->draw(_owner);
}

void IkaSpecialTyphoon::exit(Ika* _owner)
{
	_owner->fly(5.0);
	_owner->init_paint_scale();
	_owner->init_special_gauge_rate();
	_owner->init_mask_radius();
	_owner->init_special_gauge();
}

IkaStateType IkaSpecialTyphoon::get_state_type()
{
	//IkaStateType ret= IkaStateType::IKA_UNDEFINED;

	//local state を返す
	//ret = m_owner->get_ika_fsm()->get_current_state()->get_state_type();

	return m_state_type;
}

bool IkaSpecialTyphoon::on_collide(Ika* _owner, CollidableObject* _obj)
{
	bool ret = false;

	ret = _owner->get_ika_fsm()->get_current_state()->on_collide(_owner, _obj);

	return ret;
}
