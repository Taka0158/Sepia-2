#include"CutScene.h"

void CutScene::update(Scene* _owner)
{
	int32 current_time = Setting::get_ms();

	if (current_time > m_end_ms)_owner->delete_cut_scene();

	m_ratio = double(current_time - m_start_ms) / double(m_end_ms - m_start_ms);
	m_ratio = Max(0.01, Min(m_ratio, 1.0));

	update_sub(_owner);
}

void CutScene::draw(Scene* _owner)
{
	draw_sub(_owner);
}
