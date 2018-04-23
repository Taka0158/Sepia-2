#pragma once


class IkaPlayerController :public IkaController 
{
public:
	IkaPlayerController(Ika*);
	~IkaPlayerController();

	//PlayerController�ł�input()�ɂ�葀�Ǘ͂�Ԃ�
	Vec2 calculate(Ika* _owner);

	//���͂̎�t�֐�
	Vec2 input(Ika* _owner);
	Vec2 input_gamepad(Ika* _owner);

	//�v���C���[��P�ɉ����ăL�[�R���t�B�O��ݒ肷��
	void set_config(ControllerType);

	bool is_pressed_swim();
private:
};