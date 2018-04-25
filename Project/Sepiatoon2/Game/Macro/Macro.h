#pragma once

#define ASSERT(str) assert(false && (str))
//--------------------------Assets------------------------------------
#define FONT_DEBUG_8 FontAsset(L"font_debug_8")
#define FONT_DEBUG_4 FontAsset(L"font_debug_4")
#define FONT_DEBUG_2 FontAsset(L"font_debug_2")
#define FONT_IKA_ALPHABET_32 FontAsset(L"font_ika_alphabet_32")
#define FONT_IKA_KANA_32 FontAsset(L"font_ika_kana_32")

#define PASS_MAP_SIMPLE	L"Assets/Images/Map/map_simple_1920_1080.png"
#define PASS_INK_0_128 L"Assets/Images/Map/ink_0_128.png"
#define PASS_INK_1_128 L"Assets/Images/Map/ink_1_128.png"
#define PASS_INK_2_128 L"Assets/Images/Map/ink_2_128.png"
#define PASS_INK_3_128 L"Assets/Images/Map/ink_3_128.png"
#define PASS_INK_4_128 L"Assets/Images/Map/ink_4_128.png"
#define PASS_INK_5_128 L"Assets/Images/Map/ink_5_128.png"
#define PASS_INK_0_600 L"Assets/Images/Map/ink_0_600.png"
#define PASS_IKA_N_A L"Assets/Images/Ika/ika_n_a.png"
#define PASS_IKA_N_C L"Assets/Images/Ika/ika_n_c.png"
#define PASS_IKA_N_N L"Assets/Images/Ika/ika_n_n.png"
#define PASS_IKA_N_S L"Assets/Images/Ika/ika_n_s.png"
#define PASS_SCENESWITCH_1 L"Assets/Images/SceneSwitch/scene_switch_1.png"
#define PASS_SCENESWITCH_IKA L"Assets/Images/SceneSwitch/scene_switch_ika.png"
#define PASS_SCENESWITCH_1_BG L"Assets/Images/SceneSwitch/scene_switch_1_bg.png"
#define PASS_IKA_CUTIN L"Assets/Images/Cutin/cutin.png"
#define PASS_SHADOW_64 L"Assets/Images/Utility/shadow_64.png"
#define PASS_TIRE_64 L"Assets/Images/MapGimmick/tire_64.png"

#define OPEN_MOVIE_IKA_CUTIN experimental::MediaPlayer::Open(L"Assets/Movies/cutin.avi")
#define PLAY_MOVIE_IKA_CUTIN(rect) experimental::MediaPlayer::Play((rect))
#define ISPLAYING_MOVIE_IKA_CUTIN experimental::MediaPlayer::IsPlaying()
#define STOP_MOVIE_IKA_CUTIN experimental::MediaPlayer::Stop()
//--------------------------当たり判定------------------------------------
//高さの差がこの値以下なら衝突
#define HEIGHT_THRESHOLD 1.0
//速さの差がこの値以下なら同じ
#define VELOCITY_THRESHOLD 0.5
//マスク半径が0とみなされる値
#define MASK_RADIUS_NULL 0.001


//--------------------------カメラパラメータ------------------------------------
//最大/最小scale値
#define CAMERA_MAX_SCALE 1.3
#define CAMERA_MIN_SCALE 0.8


//--------------------------簡易色識別------------------------------------
#define COLOR_MINE 0
#define COLOR_RIVAL 1
#define COLOR_NEUTRAL 2

//この値差以下なら同じ色とみなす閾値
#define COLOR_THRESHOLD 3

//--------------------------Singletonクラス------------------------------------
#define SCENE_MGR mine::SceneManager::getInstance()
#define OBJ_MGR ObjectManager::getInstance()
#define SETTING Setting::getInstance()
#define MSG_DIS MessageDispatcher::getInstance()
#define DEBUG Debug::getInstance()
#define SCENE_CAMERA SceneCamera::getInstance()
#define UI_MGR UIManager::getInstance()
#define OBJ_MAP_SIMPLE MapSimple::getInstance()
#define ASSET_FAC AssetFactory::getInstance()

//--------------------------ID------------------------------------
//	 MGR  CLASS	 インスタンス(1～65535)
// ID 00    00		0000 

#define UID_UNKNOWN			0x00000000

#define UID_MGR_SCENE		0x01000000

// or(| : 論理和) で　結合すること
#define UID_MGR_OBJ				0x02000000
#define UID_OBJ_MAP				0x02000001
#define ID_OBJ_TEST				0x02010000
#define ID_OBJ_IKA				0x02020000
#define ID_MAPGIMMCIK_TIRE		0x02100000

#define UID_MGR_EFFECT			0x04000000
#define UID_MGR_AUDIO			0x08000000
#define UID_MGR_UI				0x10000000
#define UID_SCENE_CAMERA		0x20000000


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
