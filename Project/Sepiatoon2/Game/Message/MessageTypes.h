#pragma once

namespace msg
{
	//���b�Z�[�W�̓��e��񋓂���
	enum class TYPE
	{
		UNKNOWN						,
		OBJMGR_DESTROY_ALL_OBJECT  ,
		SCENE_SET_CENTER ,
		MAP_PAINT
	};

	//�f�o�O�p�ɕ\�����閼�O
	String toString(TYPE _type)
	{
		String str;
		switch (_type)
		{
		case TYPE::UNKNOWN:
			str = L"UNKNOWN";
			break;
		case TYPE::OBJMGR_DESTROY_ALL_OBJECT:
			str = L"OBJMGR�F�S�j��";
			break;
		case TYPE::SCENE_SET_CENTER:
			str = L"CAMERA:���S��ݒ�";
			break;
		case TYPE::MAP_PAINT:
			str = L"MAP:�F�h��";
			break;
		}
		return str;
	}
}
