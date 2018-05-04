#pragma once


class Tire :public MapGimmick
{
public:
	Tire(Map* _map,Vec2 _init_pos);
	~Tire();

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
		m_max_force = 10.0;
		m_max_speed = 30.0;
		m_max_turn_rate = 0.01;
		m_friction = 0.02;
	}

	bool handle_message(const Telegram& _msg)override;
	bool handle_collide(CollidableObject* _obj)override;
private:
	void restrain();
private:
	bool on_collide(CollidableObject* _obj)override;
	static int m_next_valid_id;
	Map* m_map;
};

int Tire::m_next_valid_id = 0;