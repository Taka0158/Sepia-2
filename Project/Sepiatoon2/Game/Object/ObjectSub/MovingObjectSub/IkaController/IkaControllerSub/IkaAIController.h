#pragma once

class IkaAIController :public IkaController 
{
public:
	IkaAIController(Ika*);
	~IkaAIController();

	Vec2 calculate(Ika* _owner);

	bool is_pressed_swim();
private:
};