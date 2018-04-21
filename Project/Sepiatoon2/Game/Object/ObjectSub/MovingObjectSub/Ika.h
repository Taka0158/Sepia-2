#pragma once

class Map;
class IkaState;
class IkaController;

class Ika :public MovingObject
{
	//friend class IkaState;
	//friend class IkaController;
public:
	Ika(Map* _map,ControllerType _controller_type,Vec2 _p,Color _color,TeamType _team_type,CharType _char_type,SpecialType _special_type);
	~Ika();

	void initialize();
	void finalize();
	void update();
	void draw();
	void mask_update();

	void debug_update();
	void debug_draw();

	void set_id();
	
	//Char�ɉ����Ă�MovingObject�̃p�����[�^�ݒ�
	void set_moving_parm();

	//������������
	void behavior_update();

	//Map�ɃC���N���Ԃ��܂���֐�
	void paint();

	//State�ύX
	void change_state(IkaState*);

	//���W�̐���
	void restrain();

	//�e�N�X�`���̔{��
	double get_tex_scale() { return 0.25; };

	//�����N���X�ȉ��ŌĂяo�����p�����[�^�̕␳
	void set_moving_parm(double _mass, double _max_speed, double _max_force, double _max_turn_rate, double _friction);

	//�m�[�}�����
	Texture& get_tex_n() { return m_tex_n; }
	//�������
	Texture& get_tex_c() { return m_tex_c; }
	//�j�����
	Texture& get_tex_s() { return m_tex_s; }
	//�{����
	Texture& get_tex_a() { return m_tex_a; }

	Color get_color() { return m_color; }
	TeamType get_team_type(){ return m_team_type; }
	CharType get_char_type() { return m_char_type; }
	SpecialType get_special_type() { return m_special_type; }
	ControllerType get_controller_type() { return m_controller_type; }
	Vec2 get_init_pos() { return m_init_pos; }
	Vec2 get_target_pos() { return m_target_pos; }
	Map* get_map() { return m_map; }
	Color get_rival_color() { return m_rival_color; }

	void set_init_pos(Vec2 _p) { m_init_pos = _p; }

	bool handle_message(const Telegram&)override;
	bool on_message(const Telegram&);

private:
	//�摜�̓o�^
	void regist_texture(CharType);
	//�R���g���[���N���X�̊��蓖��
	void regist_controller(ControllerType);
	//����̐F��ݒ肷��
	void set_rival_color();
protected:
	Vec2 m_target_pos;

private:
	//�C�J�̏�Ԃ�\��
	std::unique_ptr<IkaState> m_ika_state;

	//�C�J�̃R���g���[���N���X
	std::unique_ptr<IkaController> m_controller;
	
	//�J�n���W
	Vec2 m_init_pos;

	//MAP���
	Map* m_map;

	//�e��p�����[�^
	Color m_color;
	Color m_rival_color;
	TeamType m_team_type;
	CharType m_char_type;
	SpecialType m_special_type;
	ControllerType m_controller_type;

	//�摜�f�[�^
	Texture m_tex_n;
	Texture m_tex_c;
	Texture m_tex_s;
	Texture m_tex_a;

	static int m_next_valid_id;

};

int Ika::m_next_valid_id = 0;

#include"IkaState\IkaState.h"
#include"IkaController\IkaController.h"