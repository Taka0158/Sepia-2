#include"MessageDispatcher.h"

//��a��include
#include"../Object/ObjectManager.h"
#include"../Camera/SceneCamera.h"

void MessageDispatcher::dispatch_message(double _dispatch_time,
	ID _sender_id,
	ID _receiver_id,
	msg::TYPE _msg,
	void* _exInfo)
{
	//�͂���̃|�C���^���󂯎��
	Entity* receiver = get_entity_from_id(_receiver_id);

	//�ו��̍쐬
	Telegram telegram(_dispatch_time*MSG_SEC, _sender_id, _receiver_id, _msg, _exInfo);

	//�f�o�b�O�p�e�L�X�g�̒ǉ�
	DEBUG->regist(DebugText(3.0 + _dispatch_time / MSG_SEC,L"���M:"+ to_hex(_sender_id) + L"-->"+ to_hex(_receiver_id) + L"<" + msg::toString(_msg) + L">"));

	//�����z�B�̏ꍇ
	if (_dispatch_time <= 0.0)
	{
		discharge(receiver, telegram);
	}					
	else
	{
		double current_time = Setting::stopwatch.ms();
		telegram.dispatch_time = current_time + _dispatch_time;
		telegrams.insert(telegram);
	}
}

bool MessageDispatcher::dispatch_delayed_message()
{
	if (telegrams.size() == 0)return true;

	//���ݎ���
	double current_time = Setting::stopwatch.ms();

	//�z�B���Ԃ��߂������b�Z�[�W�𑗐M����
	while (telegrams.begin()->dispatch_time < current_time&&telegrams.begin()->dispatch_time>0)
	{
		//�擪�̃��b�Z�[�W�̓ǂݍ���
		Telegram telegram = *(telegrams.begin());
		
		//��M�҂̔���
		Entity* receiver = get_entity_from_id(telegram.receiver_id);

		//���M
		discharge(receiver, telegram);

		//�L���[����폜
		telegrams.erase(telegrams.begin());

		//���b�Z�[�W���Ȃ��Ȃ�ƏI��
		if (telegrams.size() == 0)break;
	}
	return true;
}

void MessageDispatcher::discharge(Entity* _receiver, const Telegram& _msg)
{
	//�f�o�b�O�p�e�L�X�g�̒ǉ�
	DEBUG->regist(DebugText(3.0, L"��M:" + to_hex(_msg.receiver_id) + L"<--" + to_hex(_msg.sender_id) + L"<" + msg::toString(_msg.msg) + L">"));
	_receiver->handle_message(_msg);
}

void MessageDispatcher::destroy_all_message()
{
	telegrams.clear();
}

Entity* MessageDispatcher::get_entity_from_id(ID _id)
{
	Entity* ret = nullptr;
	if ((_id & ID(ID_MGR_SCENE)) != 0)
	{

	}
	else if ((_id & ID(ID_MGR_OBJ)) != 0)
	{
		if (_id == ID(ID_MGR_OBJ))
		{
			ret = OBJ_MGR;
		}
		else
		{
			ret = OBJ_MGR->get_entity_from_id(_id);
		}
	}
	else if ((_id & ID(ID_MGR_EFFECT)) != 0)
	{

	}
	else if ((_id & ID(ID_MGR_AUDIO)) != 0)
	{

	}
	else if ((_id & ID(ID_MGR_UI)) != 0)
	{

	}
	else if ((_id & ID(ID_SCENE_CAMERA)) != 0)
	{
		ret = SCENE_CAMERA;
	}
	else
	{
		ASSERT("���悪�s���ȃ��b�Z�[�W�ł�");
	}

	if (ret == nullptr)
	{
		ASSERT("���悪���݂��܂���");
	}
	else
	{
		return ret;
	}
}

void MessageDispatcher::debug_draw()
{
	Println(L"�x�����b�Z�[�W��:" , telegrams.size());
}