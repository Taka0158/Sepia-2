#pragma once

class Ika;

//Ikaの操縦クラス
class IkaController
{
public:
	IkaController(Ika* _owner) 
	{
		m_owner = _owner;
	};
	virtual ~IkaController() {};

	//合力を計算し、返す
	virtual Vec2 calculate() = 0;

	Key& get_key_up() { return m_key_up; }
	Key& get_key_down() { return m_key_down; }
	Key& get_key_right() { return m_key_right; }
	Key& get_key_lefy() { return m_key_left; }
	Key& get_key_swim() { return m_key_swim; }
protected:
	Ika* m_owner;

	Key m_key_up;
	Key m_key_down;
	Key m_key_right;
	Key m_key_left;
	Key m_key_swim;
};

#include"IkaControllerSub\IkaPlayerController.cpp"
#include"IkaControllerSub\IkaAIController.cpp"
