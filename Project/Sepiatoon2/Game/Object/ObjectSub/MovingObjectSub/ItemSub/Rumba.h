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
	bool handle_collide(Object* _obj)override;
private:
	void restrain();

	void set_direction();

	void destroy();
private:
	int timer = 0;
	bool on_collide(Object* _obj)override;
	static int m_next_valid_id;
	Map* m_map;

	//初期方向を記録する
	Vec2 m_direction;

	//移動速度
	double m_speed;

	Color m_color;

	//paintする間隔(時間)
	int m_paint_interval;

	//描画角度
	double m_angle;
};

int Rumba::m_next_valid_id = 0;
