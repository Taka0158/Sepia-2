#pragma once



class IkaStateMachine
{
public:
	IkaStateMachine(Ika*);
	~IkaStateMachine();

	void update();
	void draw();

	void change_state(IkaState* _new_state);

	void revert_to_previous_state();

	void set_current_state(IkaState* _state) { m_current_state.reset(_state); }
	void set_previous_state(IkaState* _state) { m_previous_state.reset(_state); }
	void set_global_state(IkaState* _state);

	IkaState* get_current_state() { return m_current_state.get(); };
	IkaState* get_previous_state() { return m_previous_state.get(); };
	IkaState* get_global_state() { return m_global_state.get(); };

	//¡—LŒø‚ÈStateType‚ğ•Ô‚·
	IkaStateType get_now_state();

	void delete_global_state();
	
	//global_state‚ğã‘‚«‚·‚é
	void overwrite_global_state(IkaState* _new_state);

	//Õ“Ëˆ—‚ÍŠeState‚ÉŠÛ“Š‚°
	bool on_collide(Object* _obj);

private:
	Ika* m_owner;

	std::unique_ptr<IkaState> m_current_state = nullptr;
	std::unique_ptr<IkaState> m_previous_state = nullptr;
	std::unique_ptr<IkaState> m_global_state = nullptr;
};

#include"IkaState\IkaState.h"
