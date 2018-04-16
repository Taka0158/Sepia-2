#include"UIManager.h"

UIManager::UIManager() :Entity(UID_MGR_UI)
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
}

void UIManager::update()
{
	if (m_UITime != nullptr)m_UITime->update();
}

void UIManager::draw()
{
	if (m_UITime != nullptr)m_UITime->draw();
}

void UIManager::debug_update()
{

}

void UIManager::debug_draw()
{

}


bool UIManager::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool UIManager::on_message(const Telegram& _msg)
{
	bool ret = false;

	//ˆ—

	return ret;
}


