#pragma once

class MessageDispatcher :public Singleton<MessageDispatcher>
{
	friend class Singleton<MessageDispatcher>;
	MessageDispatcher() {};
	~MessageDispatcher() {};
public:
	//メッセージを送信する
	void dispatch_message(double _dispatch_time,
		ID _sender_id,
		ID _receiver_id,
		msg::TYPE _msg,
		void* _exinfo = nullptr,
		bool _use_debug_text = true);
	//相手を直指名　即時配達
	void dispatch_message(double _dispatch_time,
		Entity* _sender_id,
		Entity* _receiver_id,
		msg::TYPE _msg,
		void* _exinfo = nullptr,
		bool _use_debug_text=true);

	//遅延メッセージの送信
	bool dispatch_delayed_message();
	bool dispatch_delayed_direct_message();

	//全てのメッセージの破棄をするメソッド
	void destroy_all_message();

	//IDから受取人のポインタを得る
	Entity* get_entity_from_id(ID _id);

	void debug_draw();

	//receiverがdeleteされるときに呼び出す
	void delete_direct_message(Entity*);

protected:
	//このメソッドはdispatch_message,dispatch_delayed_messageが利用する
	void discharge(Entity* _receiver, const Telegram& _msg);
	void discharge(Entity* _receiver, const DirectTelegram& _msg);
private:
	//遅延メッセージのコンテナ
	//ソートの優先順度はTelegram.hの<演算子参照
	std::multiset<Telegram> telegrams;
	std::multiset<DirectTelegram> direct_telegrams;

};

MessageDispatcher* MessageDispatcher::instance = nullptr;


