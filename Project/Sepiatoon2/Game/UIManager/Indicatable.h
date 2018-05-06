#pragma once

//UI表示可能なクラス
class Indicatable
{
public:
	Indicatable() {};
	virtual ~Indicatable() {};

	virtual void show_ui() = 0;
};