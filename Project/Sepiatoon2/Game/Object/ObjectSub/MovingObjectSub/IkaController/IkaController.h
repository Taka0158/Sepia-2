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
protected:
	Ika* m_owner;
};

#include"IkaControllerSub\IkaPlayerController.cpp"
#include"IkaControllerSub\IkaAIController.cpp"
