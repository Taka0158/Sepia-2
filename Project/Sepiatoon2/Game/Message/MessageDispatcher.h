#pragma once

class MessageDispatcher :public Singleton<MessageDispatcher>
{
	friend class Singleton<MessageDispatcher>;
	MessageDispatcher() {};
	~MessageDispatcher() {};
public:
	//���b�Z�[�W�𑗐M����
	void dispatch_message(double _dispatch_time,
		ID _sender_id,
		ID _receiver_id,
		msg::TYPE _msg,
		void* _exInfo = nullptr);

	//�x�����b�Z�[�W�̑��M
	bool dispatch_delayed_message();

	//�S�Ẵ��b�Z�[�W�̔j�������郁�\�b�h
	void destroy_all_message();

	//ID������l�̃|�C���^�𓾂�
	Entity* get_entity_from_id(ID _id);

	void debug_draw();

protected:
	//���̃��\�b�h��dispatch_message,dispatch_delayed_message�����p����
	void discharge(Entity* _receiver, const Telegram& _msg);
private:
	//�x�����b�Z�[�W�̃R���e�i
	//�\�[�g�̗D�揇�x��Telegram.h��<���Z�q�Q��
	std::set<Telegram> telegrams;

};

MessageDispatcher* MessageDispatcher::instance = nullptr;


