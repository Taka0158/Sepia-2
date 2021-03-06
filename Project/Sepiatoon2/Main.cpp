﻿#include <Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>
#include<memory>
#include<cassert>
#include<climits>
#include<functional>
#include<set>
#include<bitset>
#include<queue>

#include"Game\Pattern\Command.h"
#include"Game\Pattern\Singleton.h"

#include"Game\Macro\Macro.h"
#include"Game\Library\Library.cpp"
#include"Game\Asset\AssetFactory.cpp"


#include"Game\System\Setting.h"
#include"Game\System\Debug.h"

#include"Game\Base\Entity.h"

#include"Game\Message\Telegram.h"

#include"Game\UIManager\UIManager.cpp"
#include"Game\Message\MessageDispatcher.h"

#include"Game\Object\ObjectManager.cpp"
#include"Game\Scene\SceneManager.cpp"

#include"Game\Message\MessageDispatcher.cpp"


void Main()
{
	//Siv3Dアセット機能の利用
	FontAsset::Register(L"font_debug_16", 16, Typeface::Default);
	FontAsset::Register(L"font_debug_8", 8, Typeface::Default);
	FontAsset::Register(L"font_debug_4", 4, Typeface::Default);
	FontAsset::Register(L"font_debug_2", 2, Typeface::Default);

	//フォントのアセット登録
	FontManager::Register(L"Assets/Fonts/Ika_font.ttf");
	FontManager::Register(L"Assets/Fonts/Ika_font_kana.ttf");

	FontAsset::Register(L"font_ika_alphabet_32", 32, L"Project Paintball");
	FontAsset::Register(L"font_ika_kana_32", 32, L"イカモドキ");

	//シングルトンクラス生成
	SETTING;
	SCENE_CAMERA;
	OBJ_MGR;


	while (System::Update())
	{
		//経過時間計測
		Stopwatch stopwatch(true);
		ClearPrint();


		MSG_DIS->dispatch_delayed_message();
		MSG_DIS->dispatch_delayed_direct_message();

		SCENE_MGR->update();
		SCENE_MGR->debug_update();
		SCENE_MGR->draw();
		SCENE_MGR->debug_draw();

		DEBUG->update();
		DEBUG->show();
		MSG_DIS->debug_draw();
		FONT_DEBUG_16(stopwatch.ms(), L"msec").draw(320, 32,Palette::Black);
	}

}


/*
TODOIST 20180427

Inkball::Initialize()で原因不明のバグ有り




*/

/*
TODOIST20180426

Typhoon途中（TODO　衝突）
Cutin修正
同時にspecialメッセージを送ると片方が消失するバグ修正


//カメラバグ
*/

/*
TODOIST20180423

//IkaStateの挙動不審を修正
//paint()の謎の挙動を修正

//摩擦が機能していないのを修正
//ただの変数名ミス

//Collide関係(Ika同士の衝突)の処理を正確に
*/


/*
作業中の内容180420

//Object:衝突関数
//Ika:IkaState以下の実装
//Ikaの描画角度導出

//Ika:入力関数(ジョイコンも考慮)
//Ika:update内での合力計算（入力によるもの）（AIによるものは後日）
//MoivingObject：行列計算

*/

/* TODOIST
//https://qiita.com/hamukun8686/items/95471335b8a0fa1d877f
//カメラ機能の実用化

//https://github.com/Siv3D/Reference-JP/wiki/%E3%82%B7%E3%83%BC%E3%83%B3%E5%88%87%E3%82%8A%E6%9B%BF%E3%81%88(%E3%82%B7%E3%83%AB%E3%82%A8%E3%83%83%E3%83%88)
//シーン遷移の自然化

//https://github.com/Siv3D/Reference-JP/wiki/GUI%E3%81%AE%E3%82%A2%E3%83%8B%E3%83%A1%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3
//UIの作成(アニメーション)

----------------------------

色塗りアルゴリズム
O(1920*1080)は死んだ
->従来方式

----------------------------
既存の問題

fullscreenでマップをcreateすると位置がずれる（カメラPosの問題？）

ObjectManager::get_entity_from_id() が線形探索により非効率
	→二部探索

Map::get_color()関数がSCENE_CAMER部分でバグ？

IkaStateSubクラスで相互include

IkaStateが挙動不審（Map::get_color()で位置ピクセル分しかとらないのが原因か）

*/

/*仕様上注意
----------------------------

Cameraの移動を考慮に入れたマウス座標は

SCENE_CAMERA->get_mouse_pos()

で得られる
ただしScale 1 の場合のみ

----------------------------

Objectが他のObjectクラスや管理クラスに影響を与える処理を行う場合

1.MessageType にて　メッセージ名を列挙型に加え、Debug用にStringで変換定義をする

2.(宛先(ID)が未定義の場合は MessageDispatcher　にて　get_entity_from_id 関数内で定義する)
	+管理クラスが宛先IDを持つ特定のインスタンスを探す場合は同名関数にて探索方法を定義する

3.宛先の　handle_message　関数にて受け取った　Telegram　を on_message　に渡し
	MessageType に応じて 処理内容を記述する

----------------------------

Cameraの影響を受けるのは各Sceneのdraw関数において

SCENE_CAMERA->update();
{

}

のスコープ内だけである

GUI等を描画する時はこの範囲外で記述する

----------------------------

レイヤ機能

ObjectManager::create～()を呼び出す際に順序集合(set)に登録regist()

ObjectManager::check_alive()で死ぬ時にreset()を呼ぶ

----------------------------

Mapクラスは必ず左上座標が(0,0)の位置に描画される

*/


/*
懸念

Setting::stopwatch()が最大値を越えると…
→ INT_MAX 2147483.647秒　-> 24日

*/

/*
備忘録

・外部シンボルの解決法（基底クラスの基底クラスが純粋仮想関数もつ場合の継承
Object						<-		Map		 <-		 MapSimple
仮想initialize()=0		   仮想initialize(){空}	   initialize(){定義}
  
*/