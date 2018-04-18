#pragma once

namespace msg
{
	//メッセージの内容を列挙する
	enum class TYPE
	{
		UNKNOWN						,
		OBJMGR_DESTROY_ALL_OBJECT  ,
		SCENE_SET_CENTER ,
		MAP_PAINT
	};

	//デバグ用に表示する名前
	String toString(TYPE _type)
	{
		String str;
		switch (_type)
		{
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
		}
		return str;
	}
}
