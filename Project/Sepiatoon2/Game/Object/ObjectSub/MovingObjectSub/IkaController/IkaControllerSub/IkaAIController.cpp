#include"IkaAIController.h"


IkaAIController::IkaAIController(Ika* _owner) :IkaController(_owner)
{

}

IkaAIController::~IkaAIController()
{

}

Vec2 IkaAIController::calculate(Ika* _owner)
{
	Vec2 ret = Vec2(0.0, 0.0);

	//TODO

	return ret;
	   
}


bool IkaAIController::is_pressed_swim()
{
	return m_key_swim.pressed;
}