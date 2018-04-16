#pragma once


class TestObj :public Object
{
public:
	TestObj(Vec2 _p);
	~TestObj();

	void initialize();
	void finalize();
	void update();
	void draw();

	bool handle_message(const Telegram&)override;
	bool on_message(const Telegram&)override;

	void debug_update();
	void debug_draw();

	void set_id();

	static int m_next_valid_id;
private:
	double radius;
};

int TestObj::m_next_valid_id = 1;
