#pragma once


class Rumba :public Item
{
public:
	Rumba(Map* _map, Vec2 _init_pos,Color _color);
	~Rumba();

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
		m_max_speed = 3.0;
		m_max_turn_rate = 0.01;
		m_friction = 0.2;
	}

	bool handle_message(const Telegram& _msg)override;
	bool handle_collide(CollidableObject* _obj)override;
	Color get_color() { return m_color; }
	void destroy();
private:
	void restrain();

	void set_direction();

private:
	int timer = 0;
	bool on_collide(CollidableObject* _obj)override;
	static int m_next_valid_id;
	Map* m_map;

	//‰Šú•ûŒü‚ğ‹L˜^‚·‚é
	Vec2 m_direction;

	//ˆÚ“®‘¬“x
	double m_speed;

	Color m_color;

	//paint‚·‚éŠÔŠu(ŠÔ)
	int m_paint_interval;

	//•`‰æŠp“x
	double m_angle;
};

int Rumba::m_next_valid_id = 0;
