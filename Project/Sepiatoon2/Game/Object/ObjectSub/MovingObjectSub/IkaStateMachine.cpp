#include"IkaStateMachine.h"

IkaStateMachine::IkaStateMachine(Ika* _owner)
{
	m_owner = _owner;
	
}

IkaStateMachine::~IkaStateMachine()
{
	m_current_state.release();
	m_previous_state.release();
	m_global_state.release();
}

void IkaStateMachine::update()
{
	if (m_global_state)m_global_state->update(m_owner);
	else if (m_current_state)m_current_state->update(m_owner);
}

void IkaStateMachine::draw()
{
	if (m_global_state)m_global_state->draw(m_owner);
	else if (m_current_state)m_current_state->draw(m_owner);
}

void IkaStateMachine::change_state(IkaState* _new_state)
{
	if (_new_state == nullptr)ASSERT("新しいStateがNULLPTRです");

	m_current_state->exit(m_owner);

	m_previous_state = std::move(m_current_state);

	m_current_state.reset(_new_state);

	m_current_state->enter(m_owner);
}


void IkaStateMachine::revert_to_previous_state()
{
	//以前のステートにもどる
	change_state(m_previous_state.get());
}

bool IkaStateMachine::on_collide(Object* _obj)
{
	bool ret = false;

	//各State内に丸投げ
	if (m_global_state)ret = m_global_state->on_collide(m_owner,_obj);
	else if (m_current_state)ret = m_current_state->on_collide(m_owner, _obj);

	return ret;
}

IkaStateType IkaStateMachine::get_now_state()
{
	IkaStateType ret = IkaStateType::IKA_UNDEFINED;
	if (m_global_state)ret = m_global_state->get_state_type();
	else if (m_current_state)ret = m_current_state->get_state_type();
	return ret;
}

void IkaStateMachine::set_global_state(IkaState* _state)
{
	if (m_global_state == nullptr)
	{
		if (_state != nullptr)
		{
			m_global_state.reset(_state);
			m_global_state->enter(m_owner);
		}
	}
}

void IkaStateMachine::delete_global_state()
{
	{
		if (m_global_state)
		{
			m_global_state->exit(m_owner);
			m_global_state.release();
			m_global_state = nullptr;
		}
	}
}