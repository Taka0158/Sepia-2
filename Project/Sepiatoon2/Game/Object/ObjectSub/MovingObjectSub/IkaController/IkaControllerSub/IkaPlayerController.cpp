#include"IkaPlayerController.h"


IkaPlayerController::IkaPlayerController(Ika* _owner) :IkaController(_owner)
{
	set_config(_owner->get_controller_type());

}

IkaPlayerController::~IkaPlayerController()
{

}

Vec2 IkaPlayerController::calculate(Ika* _owner)
{
	Vec2 ret = Vec2(0.0, 0.0);

	ret = input(_owner);

	return ret;
}

Vec2 IkaPlayerController::input(Ika* _owner)
{
	Vec2 ret = Vec2(0.0, 0.0);

	//ゲームパッドに接続されていると有効
	ret += input_gamepad(_owner);

	if (m_key_up.pressed)ret += Vec2(0.0, -1.0);
	if (m_key_down.pressed)ret += Vec2(0.0, 1.0);
	if (m_key_right.pressed)ret += Vec2(1.0, 0.0);
	if (m_key_left.pressed)ret += Vec2(-1.0, 0.0);

	ret = clamp(ret, Vec2(-1.0, -1.0), Vec2(1.0, 1.0));

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
		m_key_swim = Input::KeyRShift;
		m_key_gamepad_swim = Gamepad(0).button(0);
		break;
	case ControllerType::PLAYER_2:
		m_key_up = Input::KeyW;
		m_key_down = Input::KeyS;
		m_key_right = Input::KeyD;
		m_key_left = Input::KeyA;
		m_key_swim = Input::KeyLShift;
		m_key_gamepad_swim = Gamepad(1).button(0);
		break;
	}

}

Vec2 IkaPlayerController::input_gamepad(Ika* _owner)
{
	Vec2 ret = Vec2(0.0, 0.0);

	switch (_owner->get_controller_type())
	{
		case ControllerType::PLAYER_1:
			if (!Gamepad(0).isConnected())break;
			ret.x = Gamepad(0).x;
			ret.y = Gamepad(0).y;
			break;
		case ControllerType::PLAYER_2:
			if (!Gamepad(1).isConnected())break;
			ret.x = Gamepad(1).x;
			ret.y = Gamepad(1).y;
			break;
	}

	if (Abs(ret.x) < 0.30)ret.x = 0.0;
	if (Abs(ret.y) < 0.30)ret.y = 0.0;

	return ret;
}

bool IkaPlayerController::is_pressed_swim()
{
	return (m_key_gamepad_swim.pressed || m_key_swim.pressed);
}