#pragma once

enum class IkaStateType {
	IKA_UNDEFINED,
	IKA_NORMAL,
	IKA_SWIM,
	IKA_SINK,
	IKA_DAMAGED,
	IKA_SPECIAL_TYPHOON,
	IKA_SPECIAL_DASH,
	IKA_SPECIAL_SUPERNOVA
};

class Map;
class IkaState;
class IkaController;
class IkaStateMachine;

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

	//���W�̐���
	void restrain();

	//�e�N�X�`���̔{��
	double get_tex_scale() { return 0.25; };

	//�摜�̕`��p�x���v�Z
	void calc_angle();

	//State�ɂ��␳
	void set_moving_parm(IkaStateType);

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
	IkaController* get_controller() { return m_controller.get(); }
	IkaStateMachine* get_ika_fsm() { return m_ika_fsm.get(); }

	double get_hp() { return m_hp; }
	double get_special_gauge() { return m_special_gauge; }


	Vec2 get_init_pos() { return m_init_pos; }
	Vec2 get_target_pos() { return m_target_pos; }
	Map* get_map() { return m_map; }
	Color get_rival_color() { return m_rival_color; }
	//0.5*Pi�͑f�ނ̌����ɂ�����
	double get_angle() { return m_angle +0.5*Pi; }

	void set_init_pos(Vec2 _p) { m_init_pos = _p; }

	bool handle_message(const Telegram&)override;
	bool handle_collide(Object* _obj)override;

	//�_���[�W���󂯂����Ă�
	void damaged(double);
	//����̃L�����^�C�v�ɉ����ă_���[�W�ʕϓ�
	void damaged(CharType);
	//HP��0�̎��Ăяo��
	void destroy();
	//������Ԋ֐�
	void burst(Vec2);
private:
	bool on_message(const Telegram&)override;
	bool on_collide(Object* _obj)override;
	//�摜�̓o�^
	void regist_texture(CharType);
	//�R���g���[���N���X�̊��蓖��
	void regist_controller(ControllerType);
	//����̐F��ݒ肷��
	void set_rival_color();
	//�p�����[�^�ύX
	void set_moving_parm(double _mass, double _max_speed, double _max_force, double _max_turn_rate, double _friction);
	//State�̃Z�b�g
	void set_state(IkaStateType);
	void set_global_state(IkaStateType);
	//�X�y�V�����̔���
	void execute_special();
	
protected:
	Vec2 m_target_pos;
private:
	//�C�J�̃R���g���[���N���X
	std::unique_ptr<IkaController> m_controller;

	//�C�J��Ԃ�FSM
	std::unique_ptr<IkaStateMachine> m_ika_fsm;
	
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

	//Char�ɂ�鏉���p�����[�^�ۑ�
	double m_init_mass;
	double m_init_max_speed;
	double m_init_max_force;
	double m_init_max_turn_rate;
	double m_init_friction;

	//�摜�f�[�^
	Texture m_tex_n;
	Texture m_tex_c;
	Texture m_tex_s;
	Texture m_tex_a;

	//�`��p�x
	double m_angle;

	static int m_next_valid_id;

	//------------------GAME���ŗ��p����p�����[�^
	double m_hp = 100.0;
	double m_special_gauge = 0.0;

};

int Ika::m_next_valid_id = 0;

#include"IkaController\IkaController.h"
#include"IkaStateMachine.cpp"
