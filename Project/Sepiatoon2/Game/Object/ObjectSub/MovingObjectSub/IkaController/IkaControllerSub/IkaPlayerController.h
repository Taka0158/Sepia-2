#pragma once


class IkaPlayerController :public IkaController 
{
public:
	IkaPlayerController(Ika*);
	~IkaPlayerController();

	//PlayerControllerではinput()により操舵力を返す
	Vec2 calculate();

	//入力の受付関数
	Vec2 input();

	//プレイヤー◯Pに応じてキーコンフィグを設定する
	void set_config(ControllerType);
private:
	Key m_key_up;
	Key m_key_down;
	Key m_key_right;
	Key m_key_left;

};