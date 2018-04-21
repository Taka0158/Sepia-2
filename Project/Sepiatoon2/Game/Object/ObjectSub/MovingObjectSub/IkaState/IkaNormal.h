#pragma once

class IkaNormal :public IkaState 
{
public:
	IkaNormal();
	~IkaNormal();

	void enter(Ika* _owner);
	void update(Ika* _owner);
	void draw(Ika* _owner);
	void exit(Ika* _owner);
private:
};