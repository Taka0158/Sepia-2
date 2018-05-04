#include"MapSimple.h"

MapSimple::MapSimple():Map(MapType::SIMPLE)
{

}

MapSimple::~MapSimple()
{
	finalize();
}

void MapSimple::initialize()
{
	finalize();

	set_background_im();
	
	m_tex_background = DynamicTexture(m_im_background);
	m_timer = 0;

	m_map_w = 1920;
	m_map_h = 1080;
	MSG_DIS->dispatch_message(0.0, UID_OBJ_MAP, UID_MAP_LOADER, msg::TYPE::MAP_LOAD, this);
}

void MapSimple::finalize()
{
	while (!que.empty()) { que.pop(); }
}


void MapSimple::update()
{
	m_timer++;
	if (m_timer%m_update_interval != 0)return;

	blend();

}

void MapSimple::draw()
{
	m_tex_background.draw();
}

void MapSimple::debug_update()
{

}

void MapSimple::debug_draw()
{
}


void MapSimple::set_background_im()
{
	m_im_background = ASSET_FAC->get_image_copy(ImageType::MAP_SIMPLE);
}