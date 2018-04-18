#pragma once

class MapSimple : public Map,public Singleton<MapSimple>
{
	friend class Singleton<MapSimple>;
public:
	MapSimple();
	~MapSimple();

	void initialize()override;
	void finalize()override;

	void update()override;
	void draw()override;

	void debug_update()override;
	void debug_draw()override;

	void set_background_im()override;

private:

};

MapSimple* Singleton<MapSimple>::instance = nullptr;