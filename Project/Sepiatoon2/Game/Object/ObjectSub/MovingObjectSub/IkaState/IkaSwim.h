#pragma once

class IkaSwim :public IkaState
{
public:
	IkaSwim();
	~IkaSwim();

	void enter(Ika* _owner);
	void update(Ika* _owner);
	void draw(Ika* _owner);
	void exit(Ika* _owner);

	void input(Ika* _owner)override;
	void state(Ika* _owner)override;

	bool on_collide(Ika* _owner, Object* _obj);
private:
};