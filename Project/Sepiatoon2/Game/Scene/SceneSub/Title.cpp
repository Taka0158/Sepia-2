#include"Title.h"

#include"Option.cpp"
#include"SelectChar.cpp"

Title::Title()
{
	scene_name = L"Title";
	initialize();
}

Title::~Title()
{
	finalize();
}

void Title::initialize()
{
	finalize();
	init_background();

	m_commands.push_back(new GoToSinglePlayCommand());
	m_commands.push_back(new GoToDoublePlayCommand());
	m_commands.push_back(new GoToOptionCommand());
	m_commands.push_back(new ExitCommand());
}

void Title::finalize()
{
	for (unsigned int i = 0; i < m_commands.size(); i++)
	{
		if (m_commands[i] != nullptr)
		{
			delete m_commands[i];
			m_commands[i] = nullptr;
		}
	}
}

void Title::enter()
{				 

	m_index = 0;
}

void Title::exit()
{

}

void Title::update()
{
	m_timer++;

	common_input(0,int(m_commands.size()-1));

	update_ika_pos();
}

void Title::draw()
{
	draw_background();

	draw_command(Point(0,280*Setting::get_sc_scale()),64);

	ASSET_FAC->get_tex(ImageType::TITLE_LOGO).scale(0.75*Setting::get_sc_scale()).drawAt(Setting::get_sc().x / 2, Setting::get_sc().y / 2 - 150 +sin(m_timer*0.1)*5);
}

void Title::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new Option());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectChar());
	}
}

void Title::debug_draw()
{
	//FontAsset(L"font_debug_8")(L"Title").drawCenter(Vec2(Setting::sc_w / 2, Setting::sc_h / 2));
	Println(L"command-index : ", m_index);
}



