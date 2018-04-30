#include"CutScene.h"

bool CutScene::update(Scene* _owner)
{
	int32 current_time = Setting::get_ms();


	m_ratio = double(current_time - m_start_ms) / double(m_end_ms - m_start_ms);
	m_ratio = Max(0.01, Min(m_ratio, 1.0));

	update_sub(_owner);

	if (current_time > m_end_ms)return false;
	else return true;

}

void CutScene::draw(Scene* _owner)
{
	draw_sub(_owner);
}
