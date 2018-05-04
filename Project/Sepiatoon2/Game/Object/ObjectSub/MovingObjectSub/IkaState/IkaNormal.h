#pragma once

class IkaNormal :public IkaState 
{
public:
	IkaNormal();
	~IkaNormal();

	void input(Ika* _owner)override;
	void state(Ika* _owner)override;
	
	void enter(Ika* _owner)override;
	void update(Ika* _owner)override;
	void draw(Ika* _owner)override;
	void exit(Ika* _owner)override;

	bool on_collide(Ika* _owner, CollidableObject* _obj);
private:
};