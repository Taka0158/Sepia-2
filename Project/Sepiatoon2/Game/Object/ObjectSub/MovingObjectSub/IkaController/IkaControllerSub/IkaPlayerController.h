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
	//swimボタンを何フレームおしているか
	int m_swim_pressed_frame = 0;
	//何フレームおしていたらスペシャルが発動するか
	static int m_special_threshold;
};

int IkaPlayerController::m_special_threshold = 45;

