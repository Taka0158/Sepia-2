#include"IkaIkaSwitch.h"

IkaIkaSwitch::IkaIkaSwitch():SceneSwitch(Setting::get_ms(), 1200)
{
	m_ika = ASSET_FAC->get_tex(ImageType::IKA_N_N);
	m_ika_num = 8;

	for (int i = 0; i < m_ika_num; i++)m_rect[i].setSize(Setting::get_size().x,Setting::sc_h/m_ika_num);
}

IkaIkaSwitch::~IkaIkaSwitch()
{
	
}

void IkaIkaSwitch::update_sub()
{

}

void IkaIkaSwitch::draw()
{
	int temp = Setting::sc_h / m_ika_num;
	if (m_current_state == SwitchType::FIRST)
	{
		double easing = EaseOut(0.0, double(Setting::sc_w) , Easing::Quint, m_1st_r);
		for (int i = 0; i < m_ika_num; i++)
		{
			if (i % 2 == 0)
			{
				int x = easing - double(Setting::sc_w);
				m_rect[i].setPos(x,i*temp).draw(Setting::get_color(TeamType::TEAM_A)).drawFrame(1.0, 1.0);
			}
			else
			{
				int x = easing - double(Setting::sc_w);
				m_rect[i].setPos(x, i*temp).draw(Setting::get_color(TeamType::TEAM_B)).drawFrame(1.0, 1.0);
			}
		}
		for (int i = 0; i < m_ika_num; i++)
		{
			if (i % 2 == 0)
			{
				m_ika.scale(0.5*Setting::get_sc_scale()).rotate(Pi*0.5).drawAt(easing, (i + 0.5)*Setting::sc_h / m_ika_num, Setting::get_color(TeamType::TEAM_A));
			}
			else
			{
				m_ika.scale(0.5*Setting::get_sc_scale()).rotate(Pi*0.5).drawAt(easing, (i + 0.5)*Setting::sc_h / m_ika_num, Setting::get_color(TeamType::TEAM_B));
			}
		}
	}
	else
	{
		double easing = EaseOut(double(Setting::sc_w), 0.0, Easing::Quint, m_2nd_r);
		for (int i = 0; i < m_ika_num; i++)
		{
			if (i % 2 == 0)
			{
				int x = easing - double(Setting::sc_w);
				m_rect[i].setPos(x, i*temp).draw(Setting::get_color(TeamType::TEAM_A)).drawFrame(1.0,1.0);
			}
			else
			{
				int x = easing - double(Setting::sc_w);
				m_rect[i].setPos(x, i*temp).draw(Setting::get_color(TeamType::TEAM_B)).drawFrame(1.0, 1.0);
			}
		}
		for (int i = 0; i < m_ika_num; i++)
		{
			if (i % 2 == 0)
			{
				m_ika.scale(0.5*Setting::get_sc_scale()).rotate(-Pi*0.5).drawAt(easing, (i + 0.5)*Setting::sc_h / m_ika_num, Setting::get_color(TeamType::TEAM_A));
			}
			else
			{
				m_ika.scale(0.5*Setting::get_sc_scale()).rotate(-Pi*0.5).drawAt(easing, (i + 0.5)*Setting::sc_h / m_ika_num, Setting::get_color(TeamType::TEAM_B));
			}
		}
	}
}