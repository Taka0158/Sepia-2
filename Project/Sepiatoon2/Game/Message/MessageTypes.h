#pragma once

namespace msg
{
	//メッセージの内容を列挙する
	enum class TYPE
	{
		UNKNOWN	,
		OBJMGR_DESTROY_ALL_OBJECT,
		SCENE_SET_CENTER ,
		MAP_PAINT,
		CHANGE_IKA_STATE,
		SET_IKA_GLOBAL_STATE,
		DELETE_IKA_GLOBAL_STATE,
		REGIST_CAMERA_SUBJECT,
		RESET_CAMERA_SUBJECT,
		SHAKE_CAMERA,
		EXECUTE_IKA_SPECIAL,
		SET_CUTIN,
		CREATE_INK_BALL
	};

	//デバグ用に表示する名前
	String toString(TYPE _type)
	{
		String str;
		switch (_type)
		{
		default:
			str = L"---";
			break;
		case TYPE::UNKNOWN:
			str = L"UNKNOWN";
			break;
		case TYPE::OBJMGR_DESTROY_ALL_OBJECT:
			str = L"OBJMGR：全破壊";
			break;
		case TYPE::SCENE_SET_CENTER:
			str = L"CAMERA:中心を設定";
			break;
		case TYPE::MAP_PAINT:
			str = L"MAP:色塗り";
			break;
		case TYPE::CHANGE_IKA_STATE:
			str = L"IKA_STATE:State変更";
			break;
		case TYPE::SET_IKA_GLOBAL_STATE:
			str = L"IKA_GLOBAL_STATE:GlobalState設定";
			break;
		case TYPE::DELETE_IKA_GLOBAL_STATE:
			str = L"IKA_GLOBAL_STATE:GlobalState削除";
			break;
		case TYPE::REGIST_CAMERA_SUBJECT:
			str = L"CAMERA:被写体に追加";
			break;
		case TYPE::RESET_CAMERA_SUBJECT:
			str = L"CAMERA:被写体から削除";
			break;
		case TYPE::SHAKE_CAMERA:
			str = L"CAMERA:画面を揺らす";
			break;
		case TYPE::EXECUTE_IKA_SPECIAL:
			str = L"イカスペシャル発動！";
			break;
		case TYPE::SET_CUTIN:
			str = L"カットイン開始";
			break;
		case TYPE::CREATE_INK_BALL:
			str = L"インクボール生成";
			break;
		}
		return str;
	}
}

