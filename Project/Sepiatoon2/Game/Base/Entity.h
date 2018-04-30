#pragma once

class Telegram;

//IDを持つクラスは必ず継承する
//管理クラスを含む
class Entity
{
public:
	Entity(ID _id)
	{
		m_id=_id;
	}
	virtual ~Entity() {};
	
	//メッセージを受け取る関数
	virtual bool handle_message(const Telegram& msg) = 0;

	ID get_id()const { return m_id; }
protected:
	ID m_id;
};

//管理クラスは継承する
//管理するクラスがなければEntityを継承する
class ManagerEntity
{
public:
	//IDからEntityのインスタンスを探す
	virtual Entity* get_entity_from_id(ID _id) = 0;
};