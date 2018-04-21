#pragma once

class IkaAIController :public IkaController 
{
public:
	IkaAIController(Ika*);
	~IkaAIController();

	Vec2 calculate();

private:
};