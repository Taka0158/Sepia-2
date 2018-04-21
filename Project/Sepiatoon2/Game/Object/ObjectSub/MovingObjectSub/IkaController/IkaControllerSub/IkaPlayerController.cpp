#include"IkaPlayerController.h"


IkaPlayerController::IkaPlayerController(Ika* _owner) :IkaController(_owner)
{
	set_config(_owner->get_controller_type());

}

IkaPlayerController::~IkaPlayerController()
{

}

Vec2 IkaPlayerController::calculate()
{
	Vec2 ret = Vec2(0.0, 0.0);

	ret = input();

	return ret;
}

Vec2 IkaPlayerController::input()
{
	Vec2 ret = Vec2(0.0, 0.0);

	if (m_key_up.pressed)ret += Vec2(0.0, -1.0);
	if (m_key_down.pressed)ret += Vec2(0.0, 1.0);
	if (m_key_right.pressed)ret += Vec2(1.0, 0.0);
	if (m_key_left.pressed)ret += Vec2(-1.0, 0.0);

	return ret;
}

void IkaPlayerController::set_config(ControllerType _type)
{
	switch (_type)
	{
	case ControllerType::PLAYER_1:
		m_key_up = Input::KeyUp;
		m_key_down = Input::KeyDown;
		m_key_right = Input::KeyRight;
		m_key_left = Input::KeyLeft;
		break;
	case ControllerType::PLAYER_2:
		m_key_up = Input::KeyW;
		m_key_down = Input::KeyS;
		m_key_right = Input::KeyD;
		m_key_left = Input::KeyA;
		break;
	}

}