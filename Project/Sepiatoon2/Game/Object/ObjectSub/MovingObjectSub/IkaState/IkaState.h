#pragma once

class Ika;

class IkaState
{
public:
	IkaState(IkaStateType _type) 
	{
		m_state_type = _type;
	};
	virtual ~IkaState() {};

	virtual void enter(Ika* _owner) = 0;
	virtual void update(Ika* _owner) = 0;
	virtual void draw(Ika* _owner) = 0;
	virtual void exit(Ika* _owner) = 0;

	//入力によるもの
	virtual void input(Ika* _owner) {};

	//状況によるもの
	virtual void state(Ika* _owner) {};

	virtual void old_pos_update(Ika* _owner)
	{
		m_old_pos = _owner->get_p();
	}

	virtual void paint(Ika* _owner)
	{
		if (m_enable_paint)
		{
			_owner->paint();
			old_pos_update(_owner);
			m_enable_paint = false;
		}
		else
		{
			if (is_enable_paint(_owner))
			{
				m_enable_paint = true;
			}
		}
	}

	//自分・相手・中立の色 を識別
	virtual bool check_ground_color(Ika* _owner)
	{
		int ret = COLOR_NEUTRAL;

		Color ground_color = _owner->get_map()->get_color(Vec2_to_Point(_owner->get_p()));

		if (ground_color == _owner->get_color())
		{
			ret = COLOR_MINE;
		}
		else if (ground_color == _owner->get_rival_color())
		{
			ret = COLOR_RIVAL;
		}

		return ret;
	}

	virtual bool is_enable_paint(Ika* _owner)
	{
		return ((m_old_pos - _owner->get_p()).length() > m_threshold_paint);
	}

	virtual void set_next_state(IkaState* _new_state)
	{
		if (m_next_state == nullptr)
		{
			m_next_state = _new_state;
		}
		else
		{
			delete m_next_state;
			m_next_state = nullptr;
			m_next_state = _new_state;
		}
	}

	virtual void execute_change_state(Ika* _owner)
	{
		if (m_next_state != nullptr)
		{
			MSG_DIS->dispatch_message(0.0, _owner, _owner, msg::TYPE::CHANGE_IKA_STATE, m_next_state);
		}
	}
protected:
	//前のペイントした座標を記録
	static Vec2 m_old_pos;

	//この距離以上前のペイント場所から離れたら更新可能となる
	static double m_threshold_paint;

	//塗れる場合true
	static bool m_enable_paint;

	//Stateタイプ
	IkaStateType m_state_type;

	//次のState
	IkaState* m_next_state = nullptr;
};

Vec2 IkaState::m_old_pos = Vec2(0.0, 0.0);
double IkaState::m_threshold_paint = 16.0;
bool IkaState::m_enable_paint = true;



#include"IkaGlobalState\IkaDamaged.cpp"
#include"IkaGlobalState\IkaSpecial.cpp"
#include"IkaNormal.cpp"
#include"IkaSwim.cpp"
#include"IkaSink.cpp"
