#include"SelectPlayMode.h"

#include"Manual.cpp"

SelectPlayMode::SelectPlayMode()
{
	scene_name = L"SelectPlayMode";
	initialize();
}

SelectPlayMode::~SelectPlayMode()
{
	finalize();
}

void SelectPlayMode::initialize()
{
	m_timer = 0;
	m_index = 0;
	init_background();
}

void SelectPlayMode::finalize()
{

}

void SelectPlayMode::enter()
{
	//シングルプレイなら
	if (Setting::get_is_single_play())
	{
		m_commands.push_back(new SetPC);
		m_commands.push_back(new SetPCCC);
	}
	else
	{
		m_commands.push_back(new SetPP);
		m_commands.push_back(new SetPCPC);
		m_commands.push_back(new SetPPCC);
	}
}

void SelectPlayMode::exit()
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

void SelectPlayMode::update()
{
	m_timer++;

	update_ika_pos();

	common_input(0, int(m_commands.size() - 1));

}

void SelectPlayMode::draw()
{
	draw_background();
	draw_command(Point(0,0), 96);
}

void SelectPlayMode::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new SelectMap());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new Manual());
	}
}

void SelectPlayMode::debug_draw()
{
	Println(L"command-index : ", m_index);
	Println(L"play_mode int-> : ", int(Setting::get_playmode()));
}