#pragma once

class Ika;

class IkaState
{
public:
	IkaState() {};
	virtual ~IkaState() {};

	virtual void enter(Ika* _owner) = 0;
	virtual void update(Ika* _owner) = 0;
	virtual void draw(Ika* _owner) = 0;
	virtual void exit(Ika* _owner) = 0;
private:
};
#include"IkaNormal.cpp"