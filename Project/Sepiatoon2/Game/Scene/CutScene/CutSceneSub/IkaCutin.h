#pragma once

/*
MediaPlayer�͍Đ����͉����`��ł��Ȃ�
VideoPlayer�͂��܂��@�\���Ȃ��c
TODO
*/
class IkaCutin :public CutScene
{
public:
	IkaCutin(Color _color);
	~IkaCutin();

	void enter(Scene*)override;
	void update_sub(Scene*)override;
	void draw_sub(Scene*)override;
	void exit(Scene*)override;
private:
	
	//�X�^�[�g���W�@��������ǂꂾ������Ă��邩
	int m_start_pos = 2000;

	Color m_color;

};