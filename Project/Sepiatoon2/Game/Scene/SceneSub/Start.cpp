#include"Start.h"


Start::Start()
{
	scene_name = L"Start";
	initialize();
}

Start::~Start()
{
	finalize();
}

void Start::initialize()
{

}

void Start::finalize()
{

}

void Start::enter()
{
	//全ての画像データをロード
	ASSET_FAC->load_all_image();

	m_timer=0;
}

void Start::exit()
{

}

void Start::update()
{
	m_timer++;
	if (m_timer == 10)
	{
		SceneParam sp=SceneParam(SceneType::TITLE, SceneSwitchType::FADEIN_FADEOUT);
		MSG_DIS->dispatch_message(0.0, UID_MGR_SCENE, UID_MGR_SCENE, msg::TYPE::SCENE_MGR_SET_NEXT_SCENE, &sp);
	}

}

void Start::draw()
{

}

void Start::debug_update()
{
	if (Input::Key1.clicked)
	{
		SCENE_MGR->change_scene(new SelectChar());
	}
	else if (Input::Key2.clicked)
	{
		SCENE_MGR->change_scene(new SelectMap());
	}
}

void Start::debug_draw()
{

}