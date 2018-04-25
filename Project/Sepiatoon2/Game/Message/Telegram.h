#pragma once
#include"MessageTypes.h"



//メッセージパッケージ
struct Telegram
{
	//送信者のエンティティタイプ
	ID sender_id = UID_UNKNOWN;
	
	//受信者のエンティティタイプ
	ID receiver_id = UID_UNKNOWN;

	//メッセージの種類・内容
	//message_types.hで定義
	msg::TYPE msg = msg::TYPE::UNKNOWN;

	//メッセージの遅延時間を設定
	//単位は秒
	double dispatch_time = -1.0;

	//追加情報
	void* extraInfo = nullptr;
	
	//デバッグ表示するかどうか
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

//直接相手指定のメッセージパッケージ
struct DirectTelegram
{
	//送信者のエンティティタイプ
	Entity* sender = nullptr;

	//受信者のエンティティタイプ
	Entity* receiver = nullptr;

	//メッセージの種類・内容
	//message_types.hで定義
	msg::TYPE msg = msg::TYPE::UNKNOWN;

	//メッセージの遅延時間を設定
	//単位は秒
	double dispatch_time = -1.0;

	//追加情報
	void* extraInfo = nullptr;

	//デバッグ表示するかどうか
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


//比較演算子のオーバーロード
//STLのコンテナで優先度を決める
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

