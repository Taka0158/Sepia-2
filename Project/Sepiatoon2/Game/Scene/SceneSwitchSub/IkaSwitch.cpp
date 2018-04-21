#include"IkaSwitch.h"

IkaSwitch::IkaSwitch() :SceneSwitch(Setting::get_ms(), 800)
{
	m_a = 255;
	m_angle = 0.0;
	m_scale = 1.0;
	
	m_ika = ASSET_FAC->get_tex_copy(ImageType::SCENESWITCH_1);
}

IkaSwitch::~IkaSwitch()
{

}

void IkaSwitch::update_sub()
{
	if (m_current_state == SwitchType::FIRST)
	{
		double easing = EaseIn(0.01, 1.0, Easing::Sine, m_1st_r);
		m_a = 255 * easing;
		m_angle = 2.0 * Pi*easing;
		m_scale = 2.0*Setting::get_sc_scale() - 0.3*easing;
	
	}
	else
	{
		double easing = EaseIn(1.00, 0.01, Easing::Sine, m_2nd_r);
		m_a = 255 * easing;
		m_angle = 2.0 * Pi*easing;
		m_scale = 2.0*Setting::get_sc_scale() - 0.3*easing;
	}

}

void IkaSwitch::draw()
{
	m_ika.scale(m_scale).rotate(m_angle).drawAt(Setting::sc_w / 2, Setting::sc_h / 2, Color(Palette::White, m_a));
}