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
#include"ItemSub\Missile.cpp"
#include"ItemSub\SpecialOrb.cpp"
#include"ItemSub\IkaBalloon.cpp"