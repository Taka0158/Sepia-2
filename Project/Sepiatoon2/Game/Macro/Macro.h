#pragma once

#define ASSERT(str) assert(false && (str))

//--------------------------Singleton�N���X------------------------------------
#define SCENE_MGR SceneManager::getInstance()
#define OBJ_MGR ObjectManager::getInstance()
#define SETTING Setting::getInstance()
#define MSG_DIS MessageDispatcher::getInstance()
#define DEBUG Debug::getInstance()

//--------------------------ID------------------------------------
//	 MGR  CLASS	 �C���X�^���X(1�`1048575)
// ID 0    00		00000 

#define ID_UNKNOWN		0xFFFFFFFF

#define ID_MGR_SCENE	0x00000000

// or(| : �_���a) �Ł@�������邱��
#define ID_MGR_OBJ		0x10000000
#define ID_OBJ_TEST		0x10100000

#define ID_MGR_EFFECT	0x20000000
#define ID_MGR_AUDIO	0x30000000
#define ID_MGR_UI		0x40000000


//-------------------------MSG--------------------------
//���̒l��菬�����x�����Ԃ������b�Z�[�W��
//���M�ҁA��M�ҁA���e�A���������ꍇ
//����Ƃ݂Ȃ�
#define MSG_DELAY 0.25

//���b�Z�[�W���M�̍ەb�\�L�Œx�����Ԃ�n���ꍇ�Ɏg�p
#define MSG_SEC 1000