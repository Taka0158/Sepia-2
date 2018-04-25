#pragma once


class Tire :public MapGimmick
{
public:
	Tire(Vec2 _init_pos);
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

	bool handle_message(const Telegram& _msg);
private:
	static int m_next_valid_id;
};

int Tire::m_next_valid_id = 0;