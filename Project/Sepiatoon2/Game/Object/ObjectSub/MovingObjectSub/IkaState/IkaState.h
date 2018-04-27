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

	//���͂ɂ�����
	virtual void input(Ika* _owner) {};

	//�󋵂ɂ�����
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

	//�����E����E�����̐F ������
	virtual bool check_ground_color(Ika* _owner)
	{
		int ret = COLOR_NEUTRAL;

		Color ground_color = _owner->get_map()->get_color(Vec2_to_Point(_owner->get_p()));

		if (is_same_color(ground_color,_owner->get_color()))
		{
			ret = COLOR_MINE;
		}
		else if (is_same_color(ground_color, _owner->get_rival_color()))
		{
			ret = COLOR_RIVAL;
		}

		return ret;
	}

	virtual bool is_enable_paint(Ika* _owner)
	{
		return ((m_old_pos - _owner->get_p()).length() > m_threshold_paint && _owner->get_height()<1.0);
	}

	virtual void set_next_state(IkaStateType _type)
	{
		m_next_state_type = _type;
		
	}

	virtual void execute_change_state(Ika* _owner)
	{
		if (m_next_state_type != IkaStateType::IKA_UNDEFINED)
		{
			MSG_DIS->dispatch_message(0.0, _owner, _owner, msg::TYPE::CHANGE_IKA_STATE, &m_next_state_type);
		}
	}

	//�Ăяo���֐��͏��L��owner�̂��̂̂�
	virtual bool on_collide(Ika* _owner,Object* _obj) { return false; };

	//������StateType��Ԃ�
	virtual IkaStateType get_state_type() { return m_state_type; }
protected:
	//�O�̃y�C���g�������W���L�^
	Vec2 m_old_pos=Vec2(0.0,0.0);

	//���̋����ȏ�O�̃y�C���g�ꏊ���痣�ꂽ��X�V�\�ƂȂ�
	static double m_threshold_paint;

	//�h���ꍇtrue
	bool m_enable_paint = true;

	//State�^�C�v
	IkaStateType m_state_type;

	IkaStateType m_next_state_type =IkaStateType::IKA_UNDEFINED;
};

double IkaState::m_threshold_paint = 8.0;



#include"IkaGlobalState\IkaDamaged.cpp"
#include"IkaGlobalState\IkaSpecialTyphoon.cpp"
#include"IkaGlobalState\IkaSpecialSupernova.cpp"
#include"IkaGlobalState\IkaSpecialDash.cpp"
#include"IkaNormal.cpp"
#include"IkaSwim.cpp"
#include"IkaSink.cpp"
