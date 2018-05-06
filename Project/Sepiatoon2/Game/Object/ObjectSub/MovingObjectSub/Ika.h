#pragma once



class Map;
class IkaState;
class IkaController;
class IkaStateMachine;

class Ika :public MovingObject,public Indicatable
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
	void init_id()override;

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

#pragma region get_function
	Color get_color() { return m_color; }
	TeamType get_team_type(){ return m_team_type; }
	CharType get_char_type() { return m_char_type; }
	SpecialType get_special_type() { return m_special_type; }
	ControllerType get_controller_type() { return m_controller_type; }
	IkaController* get_controller() { return m_controller.get(); }
	IkaStateMachine* get_ika_fsm() { return m_ika_fsm.get(); }

	double get_hp() { return m_hp; }
	double get_init_hp() { return m_init_hp; }
	double get_special_gauge() { return m_special_gauge; }
	double get_init_special_gauge() { return m_init_special_gauge; }
	double get_paint_scale() { return m_paint_scale; }
	double get_swim_jump() { return m_swim_jump; }

	Vec2 get_init_pos() { return m_init_pos; }
	Vec2 get_target_pos() { return m_target_pos; }
	Map* get_map() { return m_map; }
	Color get_rival_color() { return m_rival_color; }
	//0.5*Pi�͑f�ނ̌����ɂ�����
	double get_angle() { return m_angle + 0.5*Pi; }
#pragma endregion

	//�{���ϓ�
	void set_special_gauge(double _s) { m_special_gauge = m_init_special_gauge*_s; }
	void init_special_gauge() { m_special_gauge = m_init_special_gauge; }

	//�{���ϓ�
	void set_special_gauge_rate(double _s) { m_gauge_rate = m_init_gauge_rate*_s; }
	void init_special_gauge_rate() { m_gauge_rate = m_init_gauge_rate; }
	//�{���ϓ�
	void set_paint_scale(double _s) { m_paint_scale = m_init_paint_scale*_s; }
	void init_paint_scale() { m_paint_scale = m_init_paint_scale; }	 

	//�{���ϓ�
	void set_mask_radius(double _s) { m_mask_radius = m_init_mask_radius*_s; }
	void init_mask_radius() { m_mask_radius = m_init_mask_radius; }

	//�{���ϓ�
	void set_mask_height(double _s) { m_mask_height = m_init_mask_height*_s; }
	void init_mask_height() { m_mask_height= m_init_mask_height; }

	//�{���ϓ�
	void set_max_speed(double _s) { m_max_speed = m_init_max_speed*_s; }
	void init_max_speed() { m_max_speed= m_init_max_speed; }

	//�{���ϓ�
	void set_hp_regene_rate(double _s) { m_hp_regene_rate = m_init_hp_regene_rate*_s; }
	void init_hp_regene_rate() { m_hp_regene_rate = m_init_hp_regene_rate; }
	
	//�{���ϓ�
	void set_swim_jump(double _s) { m_swim_jump = m_init_swim_jump *_s; }
	void init_swim_jump() { m_swim_jump = m_init_swim_jump; }

	void set_init_pos(Vec2 _p) { m_init_pos = _p; }

	bool handle_message(const Telegram&)override;
	bool handle_collide(CollidableObject* _obj)override;

	void show_ui()override;

	//�_���[�W���󂯂����Ă�
	void damaged(double);
	//��O�Ȃ��_���[�W���󂯂�
	void damaged_definitely(double _damage);
	//����̃L�����^�C�v�ɉ����ă_���[�W�ʕϓ�
	void damaged(CharType);
	//HP��0�̎��Ăяo��
	void destroy();
	//�p�����[�^�̏�����
	void init_param();

	//�X�y�V�����Q�[�W�̏㏸
	void increase_special_gauge(double _value);
	//hp�̎�����
	void regene_hp();
	//Sink��Ԃ̌p���_���[�W
	void sink_damage();

	//�X�y�V�����̔���
	void execute_special();

	bool is_enable_execute_special() { return m_special_gauge >= m_max_special_gauge; }
private:
	bool on_message(const Telegram&)override;
	bool on_collide(CollidableObject* _obj)override;
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
	void overwrite_global_state(IkaStateType);

	//�L�������Ƃ̃p���[���^��ݒ�
	void set_char_param(CharType _type);
	//�X�y�V�����Q�[�W�̕\��
	void show_special_gauge();
	//�̗̓Q�[�W�̕\��
	void show_hp();

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
	double m_init_hp;
	double m_hp;
	double m_init_special_gauge;
	double m_special_gauge;

	//paint�̔��a�̔{��
	double m_init_paint_scale;
	double m_paint_scale;

	//hp�̎����񕜗�
	double m_hp_regene_rate;
	double m_init_hp_regene_rate;

	//special gauge �̂��܂�₷��
	double m_init_gauge_rate;
	double m_gauge_rate;

	//�R���W��������
	double m_init_mask_radius;

	//�R���W�����}�X�N�̍���
	double m_init_mask_height;

	//�X�y�V�����Q�[�W��MAX�l
	static double m_max_special_gauge;

	//�j����Ԃ��璵�˂鍂��
	double m_swim_jump;
	double m_init_swim_jump;
};

int Ika::m_next_valid_id = 1;
double Ika::m_max_special_gauge= 100.0;

#include"IkaController\IkaController.h"
#include"IkaStateMachine.cpp"
