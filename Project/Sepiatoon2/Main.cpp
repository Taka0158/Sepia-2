#include <Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>
#include<memory>
#include<cassert>
#include<climits>
#include<bitset>

#include"Game\Library\Library.cpp"
#include"Game\Macro\Macro.h"

#include"Game\Pattern\Command.h"
#include"Game\Pattern\Singleton.h"

#include"Game\System\Setting.h"
#include"Game\System\Debug.h"

#include"Game\Base\Entity.h"

#include"Game\Message\Telegram.h"

#include"Game\Message\MessageDispatcher.cpp"

#include"Game\Object\ObjectManager.cpp"
#include"Game\Scene\SceneManager.cpp"



void Main()
{
	//Siv3Dアセット機能の利用
	FontAsset::Register(L"font_debug_8", 8, Typeface::Black);

	SETTING;
	SCENE_CAMERA;

	while (System::Update())
	{
		ClearPrint();

		MSG_DIS->dispatch_delayed_message();

		SCENE_MGR->update();
		SCENE_MGR->debug_update();
		SCENE_MGR->draw();
		SCENE_MGR->debug_draw();

		DEBUG->update();
		MSG_DIS->debug_draw();
	}
}



/* TODOIST
https://qiita.com/hamukun8686/items/95471335b8a0fa1d877f
カメラ機能の実用化

https://github.com/Siv3D/Reference-JP/wiki/%E3%82%B7%E3%83%BC%E3%83%B3%E5%88%87%E3%82%8A%E6%9B%BF%E3%81%88(%E3%82%B7%E3%83%AB%E3%82%A8%E3%83%83%E3%83%88)
シーン遷移の自然化

https://github.com/Siv3D/Reference-JP/wiki/GUI%E3%81%AE%E3%82%A2%E3%83%8B%E3%83%A1%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3
UIの作成(アニメーション)

----------------------------

色塗りアルゴリズム



*/