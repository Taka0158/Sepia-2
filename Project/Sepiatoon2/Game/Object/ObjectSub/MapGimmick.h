#pragma once


class MapGimmick :public Object
{
public:
	MapGimmick(ID _id) :Object(_id) {};
	virtual ~MapGimmick() {};
protected:

};

#include"MapGimmickSub\Tire.cpp"