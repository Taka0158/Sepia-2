#pragma once


class IkaPlayerController :public IkaController 
{
public:
	IkaPlayerController(Ika*);
	~IkaPlayerController();

	//PlayerControllerではinput()により操舵力を返す
	Vec2 calculate(Ika* _owner);

	//入力の受付関数
	Vec2 input(Ika* _owner);
	Vec2 input_gamepad(Ika* _owner);

	//プレイヤー◯Pに応じてキーコンフィグを設定する
	void set_config(ControllerType);

	bool is_pressed_swim();
private:
};