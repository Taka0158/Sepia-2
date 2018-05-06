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
		CREATE_INK_BALL,
		SCENE_MGR_SET_NEXT_SCENE,
		REMOVE_FROM_COLLIDE_TREE,
		REGISTER_TO_COLLIDE_TREE,
		WALL_PAINT,
		MAP_LOAD,
		ALL_WALL_PAINT,
		DEFINITE_DAMAGE_OTHER,
		GET_MISSILE_TARGET,
		GIVE_MISSILE_TARGET,
		REGISTER_TO_UI,
		CREATE_ORB,
		CREATE_IKABALLOON,
		CREATE_MISSILE,
		CREATE_RUMBA,
		RESPAWN_IKA,
		CREATE_IKA,
		ALL_IKA_STATE_RESPAWN,
		GIVE_CREATED_IKA
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
		case TYPE::SCENE_MGR_SET_NEXT_SCENE:
			str = L"次のシーンへ遷移";
			break;
		case TYPE::REMOVE_FROM_COLLIDE_TREE:
			str = L"衝突木から削除";
			break;
		case TYPE::REGISTER_TO_COLLIDE_TREE:
			str = L"衝突木に追加";
			break;	
		case TYPE::WALL_PAINT:
			str = L"ブロックの下の色を黒に";
			break;
		case TYPE::MAP_LOAD:
			str = L"マップロード";
			break;
		case TYPE::ALL_WALL_PAINT:
			str = L"全ての壁色を黒に";
			break;
		case TYPE::DEFINITE_DAMAGE_OTHER:
			str = L"相手に例外なしにダメージを当たる";
			break;
		case TYPE::GET_MISSILE_TARGET:
			str = L"ミサイルの相手を探す";
			break;
		case TYPE::GIVE_MISSILE_TARGET:
			str = L"ミサイルの相手を与える";
			break;
		case TYPE::REGISTER_TO_UI:
			str = L"UIオブジェクトに登録";
			break;
		case TYPE::CREATE_ORB:
			str = L"ORB生成";
			break;
		case TYPE::CREATE_IKABALLOON:
			str = L"IKABALLOON生成";
			break;
		case TYPE::CREATE_MISSILE:
			str = L"MISSILE生成";
			break;
		case TYPE::CREATE_RUMBA:
			str = L"RUMBA生成";
			break;
		case TYPE::RESPAWN_IKA:
			str = L"IKA復活";
			break;
		case TYPE::CREATE_IKA:
			str = L"IKA生成";
			break;
		case TYPE::ALL_IKA_STATE_RESPAWN:
			str = L"全てのイカをIkaRespawnに";
			break;
		case TYPE::GIVE_CREATED_IKA:
			str = L"生成したイカを渡す";
			break;
		}
		return str;
	}
}

