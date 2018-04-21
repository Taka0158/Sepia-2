#include"Ika.h"

Ika::Ika(Map* _map,Vec2 _init_p, Color _color, TeamType _team_type, CharType _char_type, SpecialType _special_type):MovingObject(ID(ID_OBJ_IKA))
{
	m_map = _map;
	m_color = _color;
	m_team_type = _team_type;
	m_char_type = _char_type;
	m_special_type = _special_type;

	m_ika_state.reset(new IkaNormal());
	m_ika_state->enter(this);

	regist_texture(m_char_type);
	set_moving_parm();

	set_init_pos(_init_p);
	initialize();
}
Ika::~Ika()
{
	finalize();
}

void Ika::initialize()
{
	finalize();

	m_is_alive = true;
	m_p = m_init_pos;

	int m_depth = 5;

	m_mask_radius = 16.0;
}

void Ika::finalize()
{
	m_is_alive = false;
}

void Ika::update()
{
	//コリジョンマスクの座標更新
	mask_update();

	m_ika_state->update(this);

}

void Ika::draw()
{
	m_ika_state->draw(this);
}

void Ika::mask_update()
{
	m_mask.setPos(m_p);
}

void Ika::regist_texture(CharType _type)
{
	switch (_type)
	{
	case CharType::NORMAL:
		m_tex_a = ASSET_FAC->get_tex(ImageType::IKA_N_A);
		m_tex_c = ASSET_FAC->get_tex(ImageType::IKA_N_C);
		m_tex_n = ASSET_FAC->get_tex(ImageType::IKA_N_N);
		m_tex_s = ASSET_FAC->get_tex(ImageType::IKA_N_S);
		break;
	}
}

void Ika::debug_update()
{

}

void Ika::debug_draw()
{
	m_mask.drawFrame(1.0,0.0,Palette::Red);
}

void Ika::set_id()
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

void Ika::set_moving_parm()
{
	switch (m_char_type)
	{
	case CharType::NORMAL:
		//適当パラメータ
		m_mass = 1.0;
		m_max_speed = 2.0;
		m_max_force = 2.0;
		m_max_turn_rate = 1.0;
		break;
	}

}

void Ika::change_state(IkaState* _new_state)
{
	m_ika_state->exit(this);
	m_ika_state.release();
	m_ika_state.reset(_new_state);
	m_ika_state->enter(this);
}