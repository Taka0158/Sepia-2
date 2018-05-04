#pragma once


class Wall :public MapGimmick
{
public:
	Wall(Map* _map,Vec2 _init_pos);
	~Wall();

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
		m_max_force = 1.0;
		m_max_speed = 0.001;
		m_max_turn_rate = 0.01;
		m_friction = 1.0;
	}

	bool handle_message(const Telegram& _msg)override;
	bool handle_collide(CollidableObject* _obj)override;
private:
	void restrain();
private:
	bool on_message(const Telegram& _msg)override;
	bool on_collide(CollidableObject* _obj)override;
	static int m_next_valid_id;
	Map* m_map;

	//èÊéZÇ∑ÇÈêF
	Color m_color = Color(Palette::White, 255);
};

int Wall::m_next_valid_id = 0;