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
}

void Title::finalize()
{
	DEBUG->regist(DebugText(3.0, L"------------------Titleデストラクタ----------------"));
}

void Title::enter()
{				 
	//デバグ用
	//全ての画像データをロード
	ASSET_FAC->load_all_image();
}

void Title::exit()
{

}

void Title::update()
{

}

void Title::draw()
{

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
	FontAsset(L"font_debug_8")(L"Title").drawCenter(Vec2(Setting::sc_w / 2, Setting::sc_h / 2));
}

