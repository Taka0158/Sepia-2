#pragma once

//���b�Z�[�W���󂯎��܂ŉ����o���Ȃ�State
class IkaRespawn :public IkaState
{
public:
	IkaRespawn();
	~IkaRespawn();

	void enter(Ika* _owner)override;
	void update(Ika* _owner)override;
	void draw(Ika* _owner)override;
	void exit(Ika* _owner)override;
private:
};
