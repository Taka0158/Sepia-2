#pragma once

/*
MediaPlayer�͍Đ����͉����`��ł��Ȃ�
VideoPlayer�͂��܂��@�\���Ȃ��c
TODO
*/
class IkaCutin :public CutScene
{
public:
	IkaCutin();
	~IkaCutin();

	void enter(Scene*)override;
	void update_sub(Scene*)override;
	void draw_sub(Scene*)override;
	void exit(Scene*)override;
private:
	//�g�p���铮��̃|�C���^
	VideoPlayer* m_using_video=nullptr;
	
	//�X�^�[�g���W�@��������ǂꂾ������Ă��邩
	int m_start_pos = 300;

	//�\���̈�
	Rect m_region = Rect(Point(0.0, 0.0), Vec2_to_Point(Setting::get_sc()));
};