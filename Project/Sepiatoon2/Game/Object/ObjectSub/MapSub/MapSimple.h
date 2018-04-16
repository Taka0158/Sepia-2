#pragma once

class MapSimple : public Map,public Singleton<MapSimple>
{
	friend class Singleton<MapSimple>;
public:
	MapSimple();
	~MapSimple();

	void initialize()override;
	void finalize() override;

	void enter()override;
	void update()override;
	void draw()override;
	void exit()override;

	void debug_update()override;
	void debug_draw()override;

	bool handle_message(const Telegram&)override;
	bool on_message(const Telegram&)override;
private:
};												

MapSimple* Singleton<MapSimple>::instance = nullptr;