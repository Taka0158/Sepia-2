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