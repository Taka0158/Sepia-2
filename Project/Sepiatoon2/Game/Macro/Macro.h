#pragma once

#define ASSERT(str) assert(false && (str))

//--------------------------Singletonクラス------------------------------------
#define SCENE_MGR SceneManager::getInstance()
#define OBJ_MGR ObjectManager::getInstance()
#define SETTING Setting::getInstance()
#define MSG_DIS MessageDispatcher::getInstance()
#define DEBUG Debug::getInstance()

//--------------------------ID------------------------------------
//	 MGR  CLASS	 インスタンス(1～1048575)
// ID 0    00		00000 

#define ID_UNKNOWN		0xFFFFFFFF

#define ID_MGR_SCENE	0x00000000

// or(| : 論理和) で　結合すること
#define ID_MGR_OBJ		0x10000000
#define ID_OBJ_TEST		0x10100000

#define ID_MGR_EFFECT	0x20000000
#define ID_MGR_AUDIO	0x30000000
#define ID_MGR_UI		0x40000000


//-------------------------MSG--------------------------
//この値より小さい遅延時間をもつメッセージは
//送信者、受信者、内容、が等しい場合
//同一とみなす
#define MSG_DELAY 0.25

//メッセージ送信の際秒表記で遅延時間を渡す場合に使用
#define MSG_SEC 1000