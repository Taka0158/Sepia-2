#pragma once

class MapSimpleBig : public Map,public Singleton<MapSimpleBig>
{
	friend class Singleton<MapSimpleBig>;
public:
	MapSimpleBig();
	~MapSimpleBig();

	void initialize()override;
	void finalize()override;

	void update()override;
	void draw()override;

	void debug_update()override;
	void debug_draw()override;

	void set_background_im()override;

private:

};

MapSimpleBig* Singleton<MapSimpleBig>::instance = nullptr;