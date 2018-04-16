#include"MapSimple.h"

MapSimple::MapSimple() :Map(UID_OBJ_MAP_SIMPLE)
{
	set_id();
	initialize();
	m_background = Texture(L"Assets/Images/Map/Map_Grid_1920_1080_32.png");
}

MapSimple::~MapSimple()
{
	finalize();
}

void MapSimple::initialize()
{
	finalize();
}

void MapSimple::finalize()
{
	REP(i, m_map_w)REP(j, m_map_h)m_vertex[i][j] = 0.0;
}

void MapSimple::enter()
{
	initialize();

}

void MapSimple::exit()
{
	finalize();
}

void MapSimple::update()
{
	//calc_grid();

	interpolation_vertex();
	
	calc_all_vertex();
}

void MapSimple::draw()
{
	m_background.draw(Vec2(0, 0));
}

void MapSimple::debug_update()
{
	if (Input::MouseL.clicked)
	{
		paint(Vec2_to_Point(SCENE_CAMERA->get_mouse_pos()));
	}
}

void MapSimple::debug_draw()
{
	Println(L"***MAP_SIMPLE***");
}

bool MapSimple::handle_message(const Telegram& _msg)
{
	on_message(_msg);
	return true;
}

bool MapSimple::on_message(const Telegram& _msg)
{
	bool ret = false;

	return ret;
}

void MapSimple::interpolation_vertex()
{
	REP(i, m_map_w)REP(j, m_map_h)
	{
		if (i%m_vertex_interval == 0 || j%m_vertex_interval == 0)continue;

		if (i == 0)
		{
		  //左端
		}
		if (j == 0)
		{
		   //上端
		}
		if (i == m_map_w - 1)
		{
			//右端
		}
		if (j == m_map_h - 1)
		{
			//下端
		}
		else
		{

		}

	}
}

//格子点はpaint()にのみ影響される
void MapSimple::calc_grid()
{
	JUMP_REP(i, m_map_w,m_vertex_interval)JUMP_REP(j, m_map_h, m_vertex_interval)
	{
		//格子点のみ計算
		if (i >= m_map_w || j >= m_map_h)continue;
		if (!(i%m_vertex_interval == 0 || j%m_vertex_interval == 0))continue;

		calc_vertex(m_vertex[i][j]);
	}
}

void MapSimple::calc_vertex(double& _v)
{

}

void MapSimple::calc_all_vertex()
{
	REP(i, m_map_w)REP(j, m_map_h)
	{
		double v_s = Sign(m_vertex[i][j]);
		double v_a = Abs(m_vertex[i][j]);
		
		//dry
		if (v_a <= m_threshold_dry)
		{
			EasingController<double> easing{
				m_vertex[i][j],
					0.0,
					Easing::Sine,
					double(m_dry_dur)
			};
			m_vertex[i][j] = easing.easeIn();
		}

		//clamp
		m_vertex[i][j] = clamp(m_vertex[i][j], -1.0, 1.0);
	}
}

void MapSimple::paint(Point _pos,int _paint_size)
{

}
