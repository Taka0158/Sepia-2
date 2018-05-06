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
	_owner->unable_gravity();
	_owner->fly(1.0);
	_owner->set_moving_parm(m_state_type);
	_owner->set_special_gauge_rate(0.0);

}
void IkaSpecialSupernova::update(Ika* _owner)
{
	m_timer++;


	_owner->behavior_update();

	if (m_timer < m_ready_duration)
	{
		m_tex_ready_index = get_tex_loop_index(m_tex_ready_index, NUM_OF_ANIM_EXPLOSION_READY-1, 0, NUM_OF_ANIM_EXPLOSION_READY-1, true);
	
		//inkball射出
		//fire(_owner);
	}
	else if (m_timer < m_ready_duration + m_duration)
	{
		m_tex_index = get_tex_loop_index(m_tex_index, NUM_OF_ANIM_EXPLOSION-1, 0, NUM_OF_ANIM_EXPLOSION-1, true);
		//爆発するタイミング
		if (m_tex_index == 6)
		{
			Paint p = Paint(Vec2_to_Point(_owner->get_p()), _owner->get_color(), 5.0);
			MSG_DIS->dispatch_message(0.0, _owner, _owner->get_map(), msg::TYPE::MAP_PAINT, &p, false);
		}
		if ( 5<=m_tex_index&&m_tex_index<=10)
		{
			_owner->set_mask_radius(5.0);
			_owner->set_mask_height(1000.0);
		}
		else
		{
			_owner->init_mask_radius();
			_owner->init_mask_height();
		}
	}
	else
	{
		MSG_DIS->dispatch_message(0.0, _owner, _owner, msg::TYPE::DELETE_IKA_GLOBAL_STATE, _owner);
	}

	if (_owner->get_height() > 100)_owner->set_height(100);
}
void IkaSpecialSupernova::draw(Ika* _owner)
{
	Println(L"IkaSpecialSupernova");

	_owner->draw_shadow();

	double angle = _owner->get_angle();
	double scale = _owner->get_tex_scale();
	_owner->get_tex_a().scale(scale).rotate(angle).drawAt(_owner->get_pos_height(), _owner->get_color());
	
	if (m_timer < m_ready_duration)
	{
		ASSET_FAC->get_tex(ImageType::ANIM_EXPLOSION_READY, m_tex_ready_index).scale(m_scale).drawAt(_owner->get_p() + Vec2(0.0, -_owner->get_height()),_owner->get_color());
	}
	else if (m_timer < m_ready_duration + m_duration)
	{
		if (m_tex_index < NUM_OF_ANIM_EXPLOSION)
		{
			ASSET_FAC->get_tex(ImageType::ANIM_EXPLOSION, m_tex_index).scale(m_scale).drawAt(_owner->get_p() + Vec2(0.0, -_owner->get_height()), _owner->get_color());
		}
	}
}
void IkaSpecialSupernova::exit(Ika* _owner)
{
	_owner->enable_gravity();
	_owner->init_mask_radius();
	_owner->init_mask_height();
	_owner->init_special_gauge_rate();
}

void IkaSpecialSupernova::fire(Ika* _owner)
{
	if (m_timer%m_fire_interval == 0)
	{
		InkballParm ibp(_owner->get_p(), _owner->get_height(), m_fire_dir, 5.0, _owner->get_color());
		MSG_DIS->dispatch_message(0.0, _owner->get_id(), UID_MGR_OBJ, msg::TYPE::CREATE_INK_BALL, &ibp,false);
		m_fire_dir = m_fire_dir.rotate(m_angle).setLength(m_length);
		m_angle += 0.2;
		m_length += 0.02;
	}
}