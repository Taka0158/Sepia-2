#pragma once


class MapGimmick :public MovingObject
{
public:
	MapGimmick(ID _id) :MovingObject(_id) {};
	virtual ~MapGimmick() {};
protected:

};

#include"MapGimmickSub\Tire.cpp"