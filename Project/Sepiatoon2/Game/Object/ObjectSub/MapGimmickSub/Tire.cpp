#include"Tire.h"

Tire::Tire(Vec2 _init_pos) :MapGimmick(ID(ID_MAPGIMMCIK_TIRE))
{
	set_id();
	initialize();
	m_pos = _init_pos;
}

Tire::~Tire()
{

}

void Tire::initialize()
{
	finalize();
	m_is_alive = true;
	m_depth = 0;
	m_init_depth = 0;
	m_mask_radius = 32.0;
}

void Tire::finalize()
{

}

void Tire::update()
{
	mask_update();
}

void Tire::draw()
{
	ASSET_FAC->get_tex(ImageType::TIRE_64).drawAt(m_pos);
}

void Tire::debug_update()
{

}

void Tire::debug_draw()
{
	m_mask.drawFrame(1.0,0.0,Palette::Red);
	FONT_DEBUG_8(to_hex(m_id)).drawCenter(m_pos, Palette::Black);
}

void Tire::set_id()
{
	if (m_next_valid_id < 0xFFFF)
	{
		m_id |= m_next_valid_id;
		m_next_valid_id++;
	}
	else
	{
		ASSERT(L"オブジェクトのID割り当てが上限を超えました");
	}
}
void Tire::init_id()
{
	m_next_valid_id = 0;
}


bool Tire::handle_message(const Telegram& _msg)
{
	//NONE
	return true;
}


void Tire::mask_update()
{
	m_mask.setPos(m_pos).setSize(m_mask_radius);
}