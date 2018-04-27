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
		void* _exinfo = nullptr,
		bool _use_debug_text = true);
	//����𒼎w���@�����z�B
	void dispatch_message(double _dispatch_time,
		Entity* _sender_id,
		Entity* _receiver_id,
		msg::TYPE _msg,
		void* _exinfo = nullptr,
		bool _use_debug_text=true);

	//�x�����b�Z�[�W�̑��M
	bool dispatch_delayed_message();
	bool dispatch_delayed_direct_message();

	//�S�Ẵ��b�Z�[�W�̔j�������郁�\�b�h
	void destroy_all_message();

	//ID������l�̃|�C���^�𓾂�
	Entity* get_entity_from_id(ID _id);

	void debug_draw();

	//receiver��delete�����Ƃ��ɌĂяo��
	void delete_direct_message(Entity*);

protected:
	//���̃��\�b�h��dispatch_message,dispatch_delayed_message�����p����
	void discharge(Entity* _receiver, const Telegram& _msg);
	void discharge(Entity* _receiver, const DirectTelegram& _msg);
private:
	//�x�����b�Z�[�W�̃R���e�i
	//�\�[�g�̗D�揇�x��Telegram.h��<���Z�q�Q��
	std::multiset<Telegram> telegrams;
	std::multiset<DirectTelegram> direct_telegrams;

};

MessageDispatcher* MessageDispatcher::instance = nullptr;


