#include"IkaNormal.h"

IkaNormal::IkaNormal()
{

}

IkaNormal::~IkaNormal()
{

}

void IkaNormal::enter(Ika* _owner)
{
	old_pos_update(_owner);
}

void IkaNormal::update(Ika* _owner)
{

	_owner->behavior_update();

	paint(_owner);

	//State‘JˆÚˆ—
}

void IkaNormal::draw(Ika* _owner)
{
	Println(L"IkaNormal");
	//TODO
	double angle = Acos(_owner->get_heading().dot(Vec2(1.0,0.0)));
	double scale = _owner->get_tex_scale();
	_owner->get_tex_n().scale(scale).rotate(angle).drawAt(_owner->get_p(), _owner->get_color());
}

void IkaNormal::exit(Ika* _owner)
{

}