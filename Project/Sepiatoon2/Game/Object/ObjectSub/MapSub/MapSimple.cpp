#include"MapSimple.h"

MapSimple::MapSimple()
{
	initialize();
}

MapSimple::~MapSimple()
{
	finalize();
}

void MapSimple::initialize()
{
	finalize();

	set_background_im();
	
	m_tex_background = Texture(m_im_background);
	m_update_interval = 2;
	m_timer = 0;
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

	m_tex_background = Texture(m_im_background);
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
	Println(L"***MAP_SIMPLE***");
}


void MapSimple::set_background_im()
{
	m_im_background = ASSET_FAC->get_image_copy(ImageType::MAP_SIMPLE);
}