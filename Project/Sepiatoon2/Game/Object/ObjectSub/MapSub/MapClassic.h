#pragma once

class MapClassic : public Map,public Singleton<MapClassic>
{
	friend class Singleton<MapClassic>;
public:
	MapClassic();
	~MapClassic();

	void initialize()override;
	void finalize()override;

	void update()override;
	void draw()override;

	void debug_update()override;
	void debug_draw()override;

	void set_background_im()override;

private:

};

MapClassic* Singleton<MapClassic>::instance = nullptr;