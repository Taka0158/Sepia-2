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
	
	m_tex_background = DynamicTexture(m_im_background);
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
	/*
	for (int i = 0; i < m_map_w/32; i++)
	{
		for (int j = 0; j < m_map_h/32; j++)
		{
			FONT_DEBUG_4(i,L",",j).drawCenter(Vec2(i*32+16, j*32+16),Palette::Black);
		}
	}
	*/
}


void MapSimple::set_background_im()
{
	m_im_background = ASSET_FAC->get_image_copy(ImageType::MAP_SIMPLE);
}