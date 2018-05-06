#pragma once


class Inkball :public Item
{
public:
	Inkball(Map* _map,
		Vec2 _init_pos,
		double _init_height,
		Vec2 _dir,
		double _fly_strength,
		Color _color,
		double _paint_scale=1.0);
	~Inkball();

	void initialize()override;
	void finalize()override;
	void update()override;
	void draw()override;

	void debug_update()override;
	void debug_draw()override;

	void mask_update()override;

	void set_id()override;
	void init_id()override;

	void behavior_update();

	void set_moving_parm()override
	{
		m_max_force = 5.0;
		m_max_speed = 10.0;
		m_max_turn_rate = 0.01;
		m_friction = 0.2;
		m_gravity = 0.05;
	}

	bool handle_message(const Telegram& _msg)override;
	bool handle_collide(CollidableObject* _obj)override;

	Color get_color()override { return m_color; };
private:
	void restrain();
	void destroy();
private:
	int timer = 0;
	bool on_collide(CollidableObject* _obj)override;
	static int m_next_valid_id;
	Map* m_map;

	//�����������L�^����
	Vec2 m_direction;

	//�ړ����x
	double m_speed;

	Color m_color;

	//�`��p�x
	double m_angle;

	//�C���N�h��͈͔{��
	double m_paint_scale;
};

int Inkball::m_next_valid_id = 0;
