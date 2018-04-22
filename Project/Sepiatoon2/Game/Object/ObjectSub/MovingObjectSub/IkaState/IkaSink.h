#pragma once

class IkaSink:public IkaState
{
public:
	IkaSink();
	~IkaSink();

	void input(Ika* _owner)override;
	void state(Ika* _owner)override;

	void enter(Ika* _owner)override;
	void update(Ika* _owner)override;
	void draw(Ika* _owner)override;
	void exit(Ika* _owner)override;


private:
};