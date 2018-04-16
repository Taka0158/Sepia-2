#include"MessageDispatcher.h"

//苦渋のinclude
#include"../Object/ObjectManager.h"
#include"../Camera/SceneCamera.h"

void MessageDispatcher::dispatch_message(double _dispatch_time,
	ID _sender_id,
	ID _receiver_id,
	msg::TYPE _msg,
	void* _exInfo)
{
	//届け先のポインタを受け取る
	Entity* receiver = get_entity_from_id(_receiver_id);

	//荷物の作成
	Telegram telegram(_dispatch_time*MSG_SEC, _sender_id, _receiver_id, _msg, _exInfo);

	//デバッグ用テキストの追加
	DEBUG->regist(DebugText(3.0 + _dispatch_time / MSG_SEC,L"送信:"+ to_hex(_sender_id) + L"-->"+ to_hex(_receiver_id) + L"<" + msg::toString(_msg) + L">"));

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

void MessageDispatcher::discharge(Entity* _receiver, const Telegram& _msg)
{
	//デバッグ用テキストの追加
	DEBUG->regist(DebugText(3.0, L"受信:" + to_hex(_msg.receiver_id) + L"<--" + to_hex(_msg.sender_id) + L"<" + msg::toString(_msg.msg) + L">"));
	_receiver->handle_message(_msg);
}

void MessageDispatcher::destroy_all_message()
{
	telegrams.clear();
}

Entity* MessageDispatcher::get_entity_from_id(ID _id)
{
	Entity* ret = nullptr;
	if ((_id & ID(ID_MGR_SCENE)) != 0)
	{

	}
	else if ((_id & ID(ID_MGR_OBJ)) != 0)
	{
		if (_id == ID(ID_MGR_OBJ))
		{
			ret = OBJ_MGR;
		}
		else
		{
			ret = OBJ_MGR->get_entity_from_id(_id);
		}
	}
	else if ((_id & ID(ID_MGR_EFFECT)) != 0)
	{

	}
	else if ((_id & ID(ID_MGR_AUDIO)) != 0)
	{

	}
	else if ((_id & ID(ID_MGR_UI)) != 0)
	{

	}
	else if ((_id & ID(ID_SCENE_CAMERA)) != 0)
	{
		ret = SCENE_CAMERA;
	}
	else
	{
		ASSERT("宛先が不明なメッセージです");
	}

	if (ret == nullptr)
	{
		ASSERT("宛先が存在しません");
	}
	else
	{
		return ret;
	}
}

void MessageDispatcher::debug_draw()
{
	Println(L"遅延メッセージ数:" , telegrams.size());
}