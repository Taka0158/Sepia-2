#pragma once
#include"MessageTypes.h"



//���b�Z�[�W�p�b�P�[�W
struct Telegram
{
	//���M�҂̃G���e�B�e�B�^�C�v
	ID sender_id = UID_UNKNOWN;
	
	//��M�҂̃G���e�B�e�B�^�C�v
	ID receiver_id = UID_UNKNOWN;

	//���b�Z�[�W�̎�ށE���e
	//message_types.h�Œ�`
	msg::TYPE msg = msg::TYPE::UNKNOWN;

	//���b�Z�[�W�̒x�����Ԃ�ݒ�
	//�P�ʂ͕b
	double dispatch_time = -1.0;

	//�ǉ����
	void* extraInfo = nullptr;

	Telegram(double _dispatch_time,
		ID _sender_id,
		ID _receiver_id,
		msg::TYPE _msg,
		void* _exInfo = nullptr):dispatch_time(_dispatch_time),
								sender_id(_sender_id),
								receiver_id(_receiver_id),
								msg(_msg),
								extraInfo(_exInfo)
	{

	}

};


//��r���Z�q�̃I�[�o�[���[�h
//STL�̃R���e�i�ŗD��x�����߂�
inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return (
		Abs(t1.dispatch_time - t2.dispatch_time) < MSG_DELAY &&
		(t1.sender_id == t2.sender_id) &&
		(t1.receiver_id == t2.receiver_id) &&
		(t1.msg == t2.msg)
		);
}
inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}
	else
	{
		return (t1.dispatch_time < t2.dispatch_time);
	}
}

