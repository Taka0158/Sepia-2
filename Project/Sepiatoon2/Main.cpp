# include <Siv3D.hpp>
#include<vector>
#include<memory>
#include<cassert>

#include"Game\Base\Base.h"
#include"Game\Macro\Macro.h"
#include"Game\Pattern\Command.h"
#include"Game\Pattern\Singleton.h"

#include"Game\Scene\SceneManager.cpp"

void Main()
{
	while (System::Update())
	{
		ClearPrint();

		SCENE_MGR->update();
		SCENE_MGR->draw();
	}
}

//シーンが正しく破棄されたかどうかー＞テレグラム実装

