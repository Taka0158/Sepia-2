#pragma once

class Ika;

class IkaState
{
public:
	IkaState() {};
	virtual ~IkaState() {};

	virtual void enter(Ika* _owner) = 0;
	virtual void update(Ika* _owner) = 0;
	virtual void draw(Ika* _owner) = 0;
	virtual void exit(Ika* _owner) = 0;

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

	virtual bool is_enable_paint(Ika* _owner)
	{
		return ((m_old_pos - _owner->get_p()).length() > m_threshold_paint);
	}
protected:
	//前のペイントした座標を記録
	static Vec2 m_old_pos;

	//この距離以上前のペイント場所から離れたら更新可能となる
	static double m_threshold_paint;

	//塗れる場合true
	static bool m_enable_paint;
};

Vec2 IkaState::m_old_pos = Vec2(0.0, 0.0);
double IkaState::m_threshold_paint = 32.0;
bool IkaState::m_enable_paint = true;



#include"IkaNormal.cpp"