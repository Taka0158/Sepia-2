#include <Siv3D.hpp>
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

	while (System::Update())
	{
		ClearPrint();

		MSG_DIS->dispatch_delayed_message();

		SCENE_MGR->update();
		SCENE_MGR->draw();

		DEBUG->update();
		MSG_DIS->debug_draw();
	}
}


