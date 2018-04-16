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

