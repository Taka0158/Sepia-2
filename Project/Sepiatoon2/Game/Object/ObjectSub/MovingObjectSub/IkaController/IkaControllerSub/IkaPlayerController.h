#pragma once


class IkaPlayerController :public IkaController 
{
public:
	IkaPlayerController(Ika*);
	~IkaPlayerController();

	//PlayerController�ł�input()�ɂ�葀�Ǘ͂�Ԃ�
	Vec2 calculate();

	//���͂̎�t�֐�
	Vec2 input();

	//�v���C���[��P�ɉ����ăL�[�R���t�B�O��ݒ肷��
	void set_config(ControllerType);


private:


};