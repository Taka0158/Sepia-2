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
		case TYPE::SCENE_MGR_SET_NEXT_SCENE:
			str = L"���̃V�[���֑J��";
			break;
		case TYPE::REMOVE_FROM_COLLIDE_TREE:
			str = L"�Փ˖؂���폜";
			break;
		case TYPE::REGISTER_TO_COLLIDE_TREE:
			str = L"�Փ˖؂ɒǉ�";
			break;	
		case TYPE::WALL_PAINT:
			str = L"�u���b�N�̉��̐F������";
			break;
		case TYPE::MAP_LOAD:
			str = L"�}�b�v���[�h";
			break;
		case TYPE::ALL_WALL_PAINT:
			str = L"�S�Ă̕ǐF������";
			break;
		case TYPE::DEFINITE_DAMAGE_OTHER:
			str = L"����ɗ�O�Ȃ��Ƀ_���[�W�𓖂���";
			break;
		case TYPE::GET_MISSILE_TARGET:
			str = L"�~�T�C���̑����T��";
			break;
		case TYPE::GIVE_MISSILE_TARGET:
			str = L"�~�T�C���̑����^����";
			break;
		case TYPE::REGISTER_TO_UI:
			str = L"UI�I�u�W�F�N�g�ɓo�^";
			break;
		case TYPE::CREATE_ORB:
			str = L"ORB����";
			break;
		case TYPE::CREATE_IKABALLOON:
			str = L"IKABALLOON����";
			break;
		case TYPE::CREATE_MISSILE:
			str = L"MISSILE����";
			break;
		case TYPE::CREATE_RUMBA:
			str = L"RUMBA����";
			break;
		case TYPE::RESPAWN_IKA:
			str = L"IKA����";
			break;
		case TYPE::CREATE_IKA:
			str = L"IKA����";
			break;
		case TYPE::ALL_IKA_STATE_RESPAWN:
			str = L"�S�ẴC�J��IkaRespawn��";
			break;
		case TYPE::GIVE_CREATED_IKA:
			str = L"���������C�J��n��";
			break;
		}
		return str;
	}
}

