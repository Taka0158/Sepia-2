#include"Map.h"
#include"MapSub\MapSimple.cpp"
Map::Map():Object(ID(UID_OBJ_MAP)) {
	m_depth = -100;
	m_is_alive = true;
	m_pos = Vec2(0.0, 0.0);
	initialize();
};

Map::~Map()
{
	finalize();
}

void Map::enter()
{
	initialize();
}

void Map::exit()
{
	finalize();
}

void Map::update()
{
	m_timer++;
	if (m_timer%m_update_interval != 0)return;

	blend();

	m_tex_background = Texture(m_im_background);
}

void Map::draw()
{
	m_tex_background.draw();
}

void Map::debug_update()
{

}

void Map::debug_draw()
{
	Println(L"***MAP_SIMPLE***");
}

bool Map::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool Map::on_message(const Telegram& _msg)
{
	bool ret = false;

	switch (_msg.msg)
	{
	case msg::TYPE::MAP_PAINT:
		paint(*((Paint*)_msg.extraInfo));
		ret = true;
	}

	return ret;
}


void Map::blend()
{
	while (!que.empty())
	{
		Paint p = que.front();
		Image img = get_random_ink();
		Size s = Size(img.width, img.height) / 2;
		rotate_image(img).write(m_im_background, Vec2_to_Point(p.pos) - s, p.color);
		que.pop();
	}
}

void Map::paint(Paint _p)
{
	Paint p = _p;
	p.pos.x = clamp(_p.pos.x, 0, m_map_w);
	p.pos.y = clamp(_p.pos.y, 0, m_map_h);
	que.push(p);
}


Color Map::get_color(Point _p)
{
	Clamp(_p, Point(0, 0), Point(m_map_w - 1, m_map_h - 1));
	return m_im_background[_p.x][_p.y];
}

Image& Map::get_random_ink()
{
	int p = Random(int(ImageType::INK_0_128), int(ImageType::INK_5_128));
	
	return ASSET_FAC->get_image(ImageType(p));
}

Image& Map::rotate_image(Image& _img)
{
	int p = Random(0, 3);

	switch (p)
	{
	case 0:
		break;
	case 1:
		_img.rotate90();
		break;
	case 2:
		_img.rotate180();
		break;
	case 3:
		_img.rotate270();
		break;
	}

	return _img;
}

