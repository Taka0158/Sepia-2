#include"MessageDispatcher.h"

//苦渋のinclude
//#include"../Object/ObjectManager.h"
//#include"../Camera/SceneCamera.h"

void MessageDispatcher::dispatch_message(double _dispatch_time,
	ID _sender_id,
	ID _receiver_id,
	msg::TYPE _msg,
	void* _exInfo,
	bool _use_debug_text,
	bool _is_delete_exinfo)
{
	//届け先のポインタを受け取る
	Entity* receiver = get_entity_from_id(_receiver_id);

	//荷物の作成
	Telegram telegram(_dispatch_time*MSG_SEC, _sender_id, _receiver_id, _msg, _exInfo, _use_debug_text,_is_delete_exinfo);

	//デバッグ用テキストの追加
	if(_use_debug_text)DEBUG->regist(DebugText(3.0 + _dispatch_time / MSG_SEC,L"送信:"+ to_hex(_sender_id) + L"-->"+ to_hex(_receiver_id) + L"<" + msg::toString(_msg) + L">"));

	//即時配達の場合
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
	void* _exInfo,
	bool _use_debug_text,
	bool _is_delete_exinfo)
{
	//届け先のポインタを受け取る
	Entity* receiver = _receiver;

	//荷物の作成
	DirectTelegram direct_telegram(_dispatch_time,_sender, _receiver, _msg, _exInfo,_use_debug_text, _is_delete_exinfo);

	//デバッグ用テキストの追加
	if(_use_debug_text)DEBUG->regist(DebugText(3.0 + _dispatch_time / MSG_SEC, L"送信:" + to_hex(_sender->get_id()) + L"-->" + to_hex(_receiver->get_id()) + L"<" + msg::toString(_msg) + L">"));

	//即時配達の場合
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
	//現在時間
	double current_time = Setting::stopwatch.ms();

	//配達時間を過ぎたメッセージを送信する
	while (telegrams.begin()->dispatch_time < current_time&&telegrams.begin()->dispatch_time>0)
	{
		//先頭のメッセージの読み込み
		Telegram telegram = *(telegrams.begin());
		
		//受信者の発見
		Entity* receiver = get_entity_from_id(telegram.receiver_id);

		//発信
		discharge(receiver, telegram);

		//キューから削除
		telegrams.erase(telegrams.begin());

		//メッセージがなくなると終了
		if (telegrams.size() == 0)break;
	}


	return true;
}

bool MessageDispatcher::dispatch_delayed_direct_message()
{
	if (direct_telegrams.size() == 0)return true;
	//現在時間
	double current_time = Setting::stopwatch.ms();

	//配達時間を過ぎたメッセージを送信する
	while (direct_telegrams.begin()->dispatch_time < current_time&&direct_telegrams.begin()->dispatch_time>0)
	{
		//先頭のメッセージの読み込み
		DirectTelegram direct_telegram = *(direct_telegrams.begin());

		//受信者の発見
		Entity* receiver = direct_telegram.receiver;

		//発信
		discharge(receiver, direct_telegram);

		//キューから削除
		direct_telegrams.erase(direct_telegrams.begin());

		//メッセージがなくなると終了
		if (direct_telegrams.size() == 0)break;
	}
}

void MessageDispatcher::discharge(Entity* _receiver, const Telegram& _msg)
{
	if (_receiver == nullptr)
	{
		DEBUG->regist(DebugText(3.0, L"--------------相手先がいないため送信不可-------------"));
		DEBUG->regist(DebugText(3.0, L"受信:???<--???<" + msg::toString(_msg.msg) + L">"));
		DEBUG->regist(DebugText(3.0, L"--------------相手先がいないため送信不可-------------"));
		return;
	}

	//デバッグ用テキストの追加
	if(_msg.show_debug_text)DEBUG->regist(DebugText(3.0, L"受信:" + to_hex(_msg.receiver_id) + L"<--" + to_hex(_msg.sender_id) + L"<" + msg::toString(_msg.msg) + L">"));
	
	_receiver->handle_message(_msg);

	//送信後削除要請が合った追加情報は削除
	if (_msg.is_delete_exinfo == true)
	{
		delete_exinfo(_msg);
	}
}

void MessageDispatcher::discharge(Entity* _receiver, const DirectTelegram& _msg)
{
	if (_receiver == nullptr)
	{
		DEBUG->regist(DebugText(3.0, L"--------------相手先がいないため送信不可-------------"));
		DEBUG->regist(DebugText(3.0, L"受信:???<--???<" + msg::toString(_msg.msg) + L">"));
		DEBUG->regist(DebugText(3.0, L"--------------相手先がいないため送信不可-------------"));
		return;
	}

	//デバッグ用テキストの追加
	if (_msg.show_debug_text)DEBUG->regist(DebugText(3.0, L"受信:" + to_hex(_msg.receiver->get_id()) + L"<--" + to_hex(_msg.sender->get_id()) + L"<" + msg::toString(_msg.msg) + L">"));
	
	//通常のTelegramに変換
	Telegram msg=Telegram(_msg.dispatch_time, 0, _msg.receiver->get_id(), _msg.msg, _msg.extraInfo,_msg.show_debug_text,_msg.is_delete_exinfo);
	
	_receiver->handle_message(msg);

	//送信後削除要請が合った追加情報は削除
	if (msg.is_delete_exinfo == true)
	{
		delete_exinfo(msg);
	}

}

void MessageDispatcher::destroy_all_message()
{
	for (auto itr : telegrams)
	{
		if (itr.is_delete_exinfo == true)
		{
			delete_exinfo(itr);
		}
	}

	telegrams.clear();
}

Entity* MessageDispatcher::get_entity_from_id(ID _id)
{
	Entity* ret = nullptr;
	if ((_id & ID(UID_MGR_SCENE)) != 0)
	{
		ret = SCENE_MGR;
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
		ret = UI_MGR;
	}
	else if ((_id & ID(UID_SCENE_CAMERA)) != 0)
	{
		ret = SCENE_CAMERA;
	}
	else if ((_id & ID(UID_COLLIDE_TREE)) != 0)
	{
		ret = COLLIDE_TREE;
	}
	else if ((_id & ID(UID_MAP_LOADER)) != 0)
	{
		ret = MAP_LOADER;
	}
	else
	{
		ASSERT("宛先が不明なメッセージです");
	}
	return ret;
}

void MessageDispatcher::debug_draw()
{
	Println(L"遅延メッセージ数:", telegrams.size());
	Println(L"遅延直接メッセージ数:" , direct_telegrams.size());
}

void MessageDispatcher::delete_direct_message(Entity* _entity)
{
	if (direct_telegrams.size() == 0)return;

	std::vector<std::set<DirectTelegram>::iterator> delete_messages;

	for (std::set<DirectTelegram>::iterator itr=direct_telegrams.begin();itr!=direct_telegrams.end();itr++)
	{
		if (itr->receiver == _entity)
		{
			delete_messages.push_back(itr);
		}
	}

	for (auto itr : delete_messages)
	{
		String msg_type = msg::toString(itr->msg);
		DEBUG->regist(DebugText(3.0, L"受取人消失 TYPE : " + msg_type));
		if (itr->is_delete_exinfo == true)delete_exinfo(*itr);
		direct_telegrams.erase(itr);
	}
}

void MessageDispatcher::delete_exinfo(const Telegram& _msg) 
{
	if (_msg.extraInfo != nullptr)
	{
		//void*　のdeleteはデストラクタが呼ばれないことに注意！
		delete _msg.extraInfo;
		DEBUG->regist(DebugText(3.0, L"-----追加情報を削除-----"));

	}
}

void MessageDispatcher::delete_exinfo(const DirectTelegram& _msg)
{
	if (_msg.extraInfo != nullptr)
	{
		//void*　のdeleteはデストラクタが呼ばれないことに注意！
		delete _msg.extraInfo;
		DEBUG->regist(DebugText(3.0, L"-----追加情報を削除-----"));
	}
}

