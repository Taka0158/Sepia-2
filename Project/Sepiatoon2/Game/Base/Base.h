#pragma once

class Base
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void initialize() = 0;
	virtual void finalize() = 0;
	virtual ~Base() {};
private:
};