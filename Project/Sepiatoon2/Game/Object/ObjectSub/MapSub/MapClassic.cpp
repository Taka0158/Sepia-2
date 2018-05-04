#include"MapClassic.h"

MapClassic::MapClassic():Map(MapType::CLASSIC)
{
}

MapClassic::~MapClassic()
{
	finalize();
}

void MapClassic::initialize()
{
	finalize();

	set_background_im();
	
	m_tex_background = DynamicTexture(m_im_background);
	m_timer = 0;

	m_map_w = 2560;
	m_map_h = 1440;

	MSG_DIS->dispatch_message(0.0, UID_OBJ_MAP, UID_MAP_LOADER, msg::TYPE::MAP_LOAD, this);
}

void MapClassic::finalize()
{
	while (!que.empty()) { que.pop(); }
}


void MapClassic::update()
{
	m_timer++;
	if (m_timer%m_update_interval != 0)return;

	blend();

}

void MapClassic::draw()
{
	m_tex_background.draw();
}

void MapClassic::debug_update()
{

}

void MapClassic::debug_draw()
{
	Println(L"MAPCLASSIC");
}


void MapClassic::set_background_im()
{
	m_im_background = ASSET_FAC->get_image_copy(ImageType::MAP_CLASSIC);
}