#pragma once

//UI�\���\�ȃN���X
class Indicatable
{
public:
	Indicatable() {};
	virtual ~Indicatable() {};

	virtual void show_ui() = 0;
};