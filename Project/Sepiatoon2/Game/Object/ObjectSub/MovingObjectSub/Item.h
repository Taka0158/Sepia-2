#pragma once


class Item :public MovingObject
{
public:
	Item(ID _id) :MovingObject(_id) {};
	virtual ~Item() {};
protected:

};

#include"ItemSub\Rumba.cpp"
#include"ItemSub\Inkball.cpp"