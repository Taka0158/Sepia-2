#include"UIManager.h"

UIManager::UIManager() :Entity(ID(UID_MGR_UI))
{
	initialize();
}

UIManager::~UIManager()
{
	finalize();
}

void UIManager::initialize()
{
	finalize();
	if (m_UITime == nullptr)
	{
		m_UITime = new UITime();
	}
}

void UIManager::finalize()
{
	if (m_UITime != nullptr)
	{
		delete m_UITime;
		m_UITime = nullptr;
	}
	if(m_indicators.empty()==false)m_indicators.clear();
}

void UIManager::update()
{
	//if (m_UITime != nullptr)m_UITime->update();
}

void UIManager::draw()
{
	//if (m_UITime != nullptr)m_UITime->draw();

	draw_indicators();
}

void UIManager::debug_update()
{

}

void UIManager::debug_draw()
{
	Println(L"UIìoò^Indicatorêî(nullpträ‹Çﬁ)ÅF", m_indicators.size());
}


bool UIManager::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool UIManager::on_message(const Telegram& _msg)
{
	bool ret = false;

	switch (_msg.msg)
	{
	case msg::TYPE::REGISTER_TO_UI:
		register_object((Indicatable*)_msg.extraInfo);
		ret = true;
		break;
	}
	return ret;
}



void UIManager::register_object(Indicatable* _ind)
{
	m_indicators.push_back(_ind);
}

void UIManager::draw_indicators()
{
	for (int i=0;i<m_indicators.size();i++)
	{
		if (m_indicators[i] != nullptr)
		{
			m_indicators[i]->show_ui();
		}
	}
}