#pragma once

//initialize��enter�֐��̗p�r��������	����
class Map :public Object
{
public:
	Map(MapType _type);
	virtual ~Map();
	virtual void initialize() {};
	virtual void finalize() {};
	//Scene�̓������ۂɌĂяo�����
	virtual void enter();
	//���C���X�V
	virtual void update() ;
	virtual void draw() ;
	//Scene���o��ۂɌĂяo�����
	virtual void exit() ;

	virtual void debug_update();
	virtual void debug_draw();

	//�P��I�u�W�F�N�g���id�̓}�N���w��
	virtual void set_id() {};
	void init_id()override {};

	bool handle_message(const Telegram&)override;
	bool on_message(const Telegram&)override;

	//�����s�N�Z���ꏊ�̐F��Ԃ�
	Color get_color(Point);

	//�}�b�v�T�C�Y��Ԃ�
	Size get_map_size() { return Size(m_map_w, m_map_h); }

	MapType get_map_type() { return m_map_type; }
protected:
	//�摜�����i�u�����h�j���s��
	void blend();
	//blend�̗\����s��
	void paint(Paint _p);
	//�w�i�摜���w�肷��
	virtual void set_background_im() = 0;
	//�H��N���X���烉���_���ɃC���N�摜�𓾂�
	Image& get_random_ink();
	//Image�������_���ɉ�]������
	Image& rotate_image(Image&);
protected:
	Image m_im_background;
	DynamicTexture m_tex_background;

	int m_map_w = 1920;
	int m_map_h = 1080;

	//�X�V�Ԋu
	int m_update_interval=1;

	int m_timer;

	//�F�h��̍s��
	std::queue<Paint> que;

	//�����̃}�b�v�^�C�v
	MapType m_map_type;
};


#include"MapSub\MapSimple.cpp"
#include"MapSub\MapSimpleBig.cpp"
#include"MapSub\MapClassic.cpp"