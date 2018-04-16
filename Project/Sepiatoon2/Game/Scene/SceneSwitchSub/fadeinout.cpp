#include"FadeInOut.h"

FadeInOut::FadeInOut():SceneSwitch(Setting::get_ms(), 500)
{
	m_a = 0;
	m_r = Rect(0, 0, Setting::sc_w, Setting::sc_h);
}

FadeInOut::~FadeInOut()
{

}

void FadeInOut::update_sub()
{
	if (m_current_state == SwitchType::FIRST)
	{
		m_a = 255 * EaseIn(0.01, 1.0, Easing::Quart, m_1st_r);
	}
	else
	{
		m_a = 255 * EaseIn(1.00, 0.01, Easing::Quart, m_2nd_r);
	}
	m_a = clamp(m_a, 0, 255);
	
}

void FadeInOut::draw()
{
	m_r.draw(Color(Palette::Black, m_a));
}