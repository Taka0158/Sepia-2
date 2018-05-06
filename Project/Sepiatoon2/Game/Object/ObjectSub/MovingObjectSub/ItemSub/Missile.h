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

	//方向転換
	void turnaround();
	//ターゲット（いかorルンバ）を探す
	void get_target();

	//上空まで達した時の振る舞いを決める
	void reach_peak();

	//雨を降らす
	void rain();

	//タイプによってパラメータを変える
	void set_missile_parameter();
private:
	int m_timer = 0;
	bool on_collide(CollidableObject* _obj)override;
	bool on_message(const Telegram& _msg);

	static int m_next_valid_id;

	Map* m_map;

	//上昇初速度
	double m_rising_speed;

	Object* m_target = nullptr;

	Color m_color;

	//描画角度
	double m_angle;
	//描画スケール
	double m_scale;

	//高さがこの値を超えたら方向転換する
	static int m_threshold;

	//ミサイルのタイプ
	MissileType m_missile_type;

	//雨を降らす範囲
	static double m_rain_area;
	
	//雨を降らす継続時間(msec)
	static int m_duration;
	
	//雨を降らす頻度
	static int m_rain_interval;
};

int Missile::m_next_valid_id = 0;
int Missile::m_threshold = 2800;
double Missile::m_rain_area= 500.0;
int Missile::m_duration = 5000;
int Missile::m_rain_interval = 120;
