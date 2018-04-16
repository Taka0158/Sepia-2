#pragma once

#define ASSERT(str) assert(false && (str))
//--------------------------Assets------------------------------------
#define FONT_IKA_ALPHABET_32 FontAsset(L"font_ika_alphabet_32")
#define FONT_IKA_KANA_32 FontAsset(L"font_ika_kana_32")

//--------------------------Singletonクラス------------------------------------
#define SCENE_MGR SceneManager::getInstance()
#define OBJ_MGR ObjectManager::getInstance()
#define SETTING Setting::getInstance()
#define MSG_DIS MessageDispatcher::getInstance()
#define DEBUG Debug::getInstance()
#define SCENE_CAMERA SceneCamera::getInstance()
#define UI_MGR UIManager::getInstance()
#define OBJ_MAP_SIMPLE MapSimple::getInstance()

//--------------------------ID------------------------------------
//	 MGR  CLASS	 インスタンス(1～65535)
// ID 00    00		0000 

#define UID_UNKNOWN			0x00000000

#define UID_MGR_SCENE		0x01000000

// or(| : 論理和) で　結合すること
#define UID_MGR_OBJ			0x02000000
#define UID_OBJ_MAP_SIMPLE	0x02000001
#define ID_OBJ_TEST			0x02010000

#define UID_MGR_EFFECT		0x04000000
#define UID_MGR_AUDIO		0x08000000
#define UID_MGR_UI			0x10000000
#define UID_SCENE_CAMERA	0x20000000


//-------------------------MSG--------------------------
//この値より小さい遅延時間をもつメッセージは
//送信者、受信者、内容、が等しい場合
//同一とみなす
#define MSG_DELAY 0.25

//メッセージ送信の際秒表記で遅延時間を渡す場合に使用
#define MSG_SEC 1000
//-------------------------REP/FOR--------------------------
#define REP(i,n) for(int i=0;i<(n);i++)
#define JUMP_REP(i,n,v) for(int i=0;i<(n);(i)+=(v))
