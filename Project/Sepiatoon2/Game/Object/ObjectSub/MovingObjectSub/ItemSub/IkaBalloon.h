#pragma once


class IkaBalloon :public Item
{
public:
	IkaBalloon(Map* _map,
		Vec2 _init_pos,
		IkaBalloonType _type);
	~IkaBalloon();

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
		m_max_speed = 5.0;
		m_max_turn_rate = 0.01;
		m_friction = 0.2;
		m_gravity = 0.05;
	}

	bool handle_message(const Telegram& _msg)override;
	bool handle_collide(CollidableObject* _obj)override;
private:
	void restrain();
	void destroy();

	Texture* get_tex();

	void explode();

	void execute_item(ItemType);

private:
	int m_timer = 0;
	bool on_collide(CollidableObject* _obj)override;
	static int m_next_valid_id;

	IkaBalloonType m_type;

	//ê⁄êGÇµÇΩëäéËÇÃêF
	Color m_color;
	
	Map* m_map;
};

int IkaBalloon::m_next_valid_id = 0;
