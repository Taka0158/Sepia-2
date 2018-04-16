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
		void* _exInfo = nullptr);

	//遅延メッセージの送信
	bool dispatch_delayed_message();

	//全てのメッセージの破棄をするメソッド
	void destroy_all_message();

	//IDから受取人のポインタを得る
	Entity* get_entity_from_id(ID _id);

	void debug_draw();

protected:
	//このメソッドはdispatch_message,dispatch_delayed_messageが利用する
	void discharge(Entity* _receiver, const Telegram& _msg);
private:
	//遅延メッセージのコンテナ
	//ソートの優先順度はTelegram.hの<演算子参照
	std::set<Telegram> telegrams;

};

MessageDispatcher* MessageDispatcher::instance = nullptr;


