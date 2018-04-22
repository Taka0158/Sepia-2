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

void MessageDispatcher::dispatch_message(double _dispatch_time,
	Entity* _sender,
	Entity* _receiver,
	msg::TYPE _msg,
	void* _exInfo)
{
	//�͂���̃|�C���^���󂯎��
	Entity* receiver = _receiver;

	//�ו��̍쐬
	DirectTelegram direct_telegram(_dispatch_time,_sender, _receiver, _msg, _exInfo);

	//�f�o�b�O�p�e�L�X�g�̒ǉ�
	DEBUG->regist(DebugText(3.0 + _dispatch_time / MSG_SEC, L"���M:" + to_hex(_sender->get_id()) + L"-->" + to_hex(_receiver->get_id()) + L"<" + msg::toString(_msg) + L">"));

	//�����z�B�̏ꍇ
	if (_dispatch_time <= 0.0)
	{
		discharge(receiver, direct_telegram);
	}
	else
	{
		double current_time = Setting::stopwatch.ms();
		direct_telegram.dispatch_time = current_time + _dispatch_time;
		direct_telegrams.insert(direct_telegram);
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

	//�z�B���Ԃ��߂������b�Z�[�W�𑗐M����
	while (direct_telegrams.begin()->dispatch_time < current_time&&direct_telegrams.begin()->dispatch_time>0)
	{
		//�擪�̃��b�Z�[�W�̓ǂݍ���
		DirectTelegram direct_telegram = *(direct_telegrams.begin());

		//��M�҂̔���
		Entity* receiver = direct_telegram.receiver;

		//���M
		discharge(receiver, direct_telegram);

		//�L���[����폜
		direct_telegrams.erase(direct_telegrams.begin());

		//���b�Z�[�W���Ȃ��Ȃ�ƏI��
		if (direct_telegrams.size() == 0)break;
	}
	return true;
}

void MessageDispatcher::discharge(Entity* _receiver, const Telegram& _msg)
{
	//�f�o�b�O�p�e�L�X�g�̒ǉ�
	DEBUG->regist(DebugText(3.0, L"��M:" + to_hex(_msg.receiver_id) + L"<--" + to_hex(_msg.sender_id) + L"<" + msg::toString(_msg.msg) + L">"));
	_receiver->handle_message(_msg);
}

void MessageDispatcher::discharge(Entity* _receiver, const DirectTelegram& _msg)
{
	//�f�o�b�O�p�e�L�X�g�̒ǉ�
	DEBUG->regist(DebugText(3.0, L"��M:" + to_hex(_msg.receiver->get_id()) + L"<--" + to_hex(_msg.sender->get_id()) + L"<" + msg::toString(_msg.msg) + L">"));
	
	//�ʏ��Telegram�ɕϊ�
	Telegram msg=Telegram(_msg.dispatch_time, _msg.sender->get_id(), _msg.receiver->get_id(), _msg.msg, _msg.extraInfo);
	
	_receiver->handle_message(msg);
}

void MessageDispatcher::destroy_all_message()
{
	telegrams.clear();
}

Entity* MessageDispatcher::get_entity_from_id(ID _id)
{
	Entity* ret = nullptr;
	if ((_id & ID(UID_MGR_SCENE)) != 0)
	{

	}
	else if ((_id & ID(UID_MGR_OBJ)) != 0)
	{
		if (_id == ID(UID_MGR_OBJ))
		{
			ret = OBJ_MGR;
		}
		else
		{
			ret = OBJ_MGR->get_entity_from_id(_id);
		}
	}
	else if ((_id & ID(UID_MGR_EFFECT)) != 0)
	{

	}
	else if ((_id & ID(UID_MGR_AUDIO)) != 0)
	{

	}
	else if ((_id & ID(UID_MGR_UI)) != 0)
	{

	}
	else if ((_id & ID(UID_SCENE_CAMERA)) != 0)
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