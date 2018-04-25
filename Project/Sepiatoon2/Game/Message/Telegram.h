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
	
	//�f�o�b�O�\�����邩�ǂ���
	bool show_debug_text = true;

	Telegram(double _dispatch_time,
		ID _sender_id,
		ID _receiver_id,
		msg::TYPE _msg,
		void* _exInfo = nullptr,
		bool _show_debug_text =true):dispatch_time(_dispatch_time),
								sender_id(_sender_id),
								receiver_id(_receiver_id),
								msg(_msg),
								extraInfo(_exInfo),
								show_debug_text(_show_debug_text)
	{

	}

};

//���ڑ���w��̃��b�Z�[�W�p�b�P�[�W
struct DirectTelegram
{
	//���M�҂̃G���e�B�e�B�^�C�v
	Entity* sender = nullptr;

	//��M�҂̃G���e�B�e�B�^�C�v
	Entity* receiver = nullptr;

	//���b�Z�[�W�̎�ށE���e
	//message_types.h�Œ�`
	msg::TYPE msg = msg::TYPE::UNKNOWN;

	//���b�Z�[�W�̒x�����Ԃ�ݒ�
	//�P�ʂ͕b
	double dispatch_time = -1.0;

	//�ǉ����
	void* extraInfo = nullptr;

	//�f�o�b�O�\�����邩�ǂ���
	bool show_debug_text = true;

	DirectTelegram(double _dispatch_time,
		Entity* _sender,
		Entity* _receiver,
		msg::TYPE _msg,
		void* _exInfo = nullptr,
		bool _show_debug_text = true) :dispatch_time(_dispatch_time),
		sender(_sender),
		receiver(_receiver),
		msg(_msg),
		extraInfo(_exInfo),
		show_debug_text(_show_debug_text)
		
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

inline bool operator==(const DirectTelegram& t1, const DirectTelegram& t2)
{
	return (
		Abs(t1.dispatch_time - t2.dispatch_time) < MSG_DELAY &&
		(t1.sender == t2.sender || t1.sender==nullptr || t2.sender==nullptr) &&
		(t1.receiver == t2.receiver || t1.receiver == nullptr || t2.receiver == nullptr) &&
		(t1.msg == t2.msg)
		);
}
inline bool operator<(const DirectTelegram& t1, const DirectTelegram& t2)
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

