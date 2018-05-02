#include"Manual.h"

#include"GameMain.cpp"

Manual::Manual()
{
	scene_name = L"Manual";
	initialize();
}

Manual::~Manual()
{
	finalize();
}

void Manual::initialize()
{

}

void Manual::finalize()
{

}

void Manual::enter()
{
	m_timer = 0;
	m_a = 0;
}

void Manual::exit()
{

}

void Manual::update()
{
	m_timer++;

	//一定時間まったら
	if (m_timer > m_wait_time)
	{
		m_a = 127 + 127 * sin(m_timer*0.1);
		//何か押されるとシーン遷移
		if (Input::AnyKeyClicked())
		{
			SceneType next_scene_type = SceneType::GAMEMAIN;
			SceneSwitchType switch_type = SceneSwitchType::IKAIKA;
			SceneParam sp = SceneParam(next_scene_type, switch_type);
			MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
		}
	}

}

void Manual::draw()
{
	draw_manual();

	if (m_timer > m_wait_time)
	{
		FONT_IKA_KANA(96)(L"キーをおしてスタート！").drawCenter(Setting::get_size().x / 2, Setting::get_size().y / 2 + 256 * Setting::get_sc_scale(), Color(Palette::White, m_a));
	}
}

void Manual::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new GameMain());
	}
}

void Manual::debug_draw()
{

}

void Manual::draw_manual()
{
	//説明画面を表示する
}
