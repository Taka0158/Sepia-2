#include"IkaNormal.h"

IkaNormal::IkaNormal()
{

}

IkaNormal::~IkaNormal()
{

}

void IkaNormal::enter(Ika* _owner)
{

}

void IkaNormal::update(Ika* _owner)
{
	//State‘JˆÚˆ—
}

void IkaNormal::draw(Ika* _owner)
{
	_owner->get_tex_n().drawAt(_owner->get_p(), _owner->get_color());
}

void IkaNormal::exit(Ika* _owner)
{

}