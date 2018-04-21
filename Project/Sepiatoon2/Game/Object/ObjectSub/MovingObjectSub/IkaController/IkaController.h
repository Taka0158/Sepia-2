#pragma once

class Ika;

//Ika�̑��c�N���X
class IkaController
{
public:
	IkaController(Ika* _owner) 
	{
		m_owner = _owner;
	};
	virtual ~IkaController() {};

	//���͂��v�Z���A�Ԃ�
	virtual Vec2 calculate() = 0;
protected:
	Ika* m_owner;
};

#include"IkaControllerSub\IkaPlayerController.cpp"
#include"IkaControllerSub\IkaAIController.cpp"
