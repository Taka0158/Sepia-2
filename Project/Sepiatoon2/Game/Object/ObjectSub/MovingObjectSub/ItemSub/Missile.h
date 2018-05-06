#pragma once

class Missile :public Item
{
public:
	Missile(Map* _map, Vec2 _init_pos, double _init_height, Color _color,MissileType _type=MissileType::NORMAL);
	~Missile();

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
	}


	bool handle_message(const Telegram& _msg)override;
	bool handle_collide(CollidableObject* _obj)override;
	Color get_color() { return m_color; }
private:
	void restrain();
	void destroy();

	//•ûŒü“]Š·
	void turnaround();
	//ƒ^[ƒQƒbƒgi‚¢‚©orƒ‹ƒ“ƒoj‚ğ’T‚·
	void get_target();

	//ã‹ó‚Ü‚Å’B‚µ‚½‚ÌU‚é•‘‚¢‚ğŒˆ‚ß‚é
	void reach_peak();

	//‰J‚ğ~‚ç‚·
	void rain();

	//ƒ^ƒCƒv‚É‚æ‚Á‚Äƒpƒ‰ƒ[ƒ^‚ğ•Ï‚¦‚é
	void set_missile_parameter();
private:
	int m_timer = 0;
	bool on_collide(CollidableObject* _obj)override;
	bool on_message(const Telegram& _msg);

	static int m_next_valid_id;

	Map* m_map;

	//ã¸‰‘¬“x
	double m_rising_speed;

	Object* m_target = nullptr;

	Color m_color;

	//•`‰æŠp“x
	double m_angle;
	//•`‰æƒXƒP[ƒ‹
	double m_scale;

	//‚‚³‚ª‚±‚Ì’l‚ğ’´‚¦‚½‚ç•ûŒü“]Š·‚·‚é
	static int m_threshold;

	//ƒ~ƒTƒCƒ‹‚Ìƒ^ƒCƒv
	MissileType m_missile_type;

	//‰J‚ğ~‚ç‚·”ÍˆÍ
	static double m_rain_area;
	
	//‰J‚ğ~‚ç‚·Œp‘±ŠÔ(msec)
	static int m_duration;
	
	//‰J‚ğ~‚ç‚·•p“x
	static int m_rain_interval;
};

int Missile::m_next_valid_id = 0;
int Missile::m_threshold = 2800;
double Missile::m_rain_area= 500.0;
int Missile::m_duration = 5000;
int Missile::m_rain_interval = 120;
