#pragma once

namespace msg
{
	//���b�Z�[�W�̓��e��񋓂���
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

	//�f�o�O�p�ɕ\�����閼�O
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
			str = L"OBJMGR�F�S�j��";
			break;
		case TYPE::SCENE_SET_CENTER:
			str = L"CAMERA:���S��ݒ�";
			break;
		case TYPE::MAP_PAINT:
			str = L"MAP:�F�h��";
			break;
		case TYPE::CHANGE_IKA_STATE:
			str = L"IKA_STATE:State�ύX";
			break;
		case TYPE::SET_IKA_GLOBAL_STATE:
			str = L"IKA_GLOBAL_STATE:GlobalState�ݒ�";
			break;
		case TYPE::DELETE_IKA_GLOBAL_STATE:
			str = L"IKA_GLOBAL_STATE:GlobalState�폜";
			break;
		case TYPE::REGIST_CAMERA_SUBJECT:
			str = L"CAMERA:��ʑ̂ɒǉ�";
			break;
		case TYPE::RESET_CAMERA_SUBJECT:
			str = L"CAMERA:��ʑ̂���폜";
			break;
		case TYPE::SHAKE_CAMERA:
			str = L"CAMERA:��ʂ�h�炷";
			break;
		case TYPE::EXECUTE_IKA_SPECIAL:
			str = L"�C�J�X�y�V���������I";
			break;
		case TYPE::SET_CUTIN:
			str = L"�J�b�g�C���J�n";
			break;
		case TYPE::CREATE_INK_BALL:
			str = L"�C���N�{�[������";
			break;
		}
		return str;
	}
}

