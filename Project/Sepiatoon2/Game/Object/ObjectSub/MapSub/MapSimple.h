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

	void paint(Point,int=4);
private:
	//m_vertex_interval*i番目　の格子点を除く
	//全ての頂点を補間する
	void interpolation_vertex();

	//m_vertex_interval*i番目の格子点
	//を計算する
	void calc_grid();

	//全ての頂点を通る計算
	void calc_all_vertex();

	//考慮頂点の内部計算
	void calc_vertex(double&);


private:
	Texture m_background;
	int m_map_w = 1920;
	int m_map_h = 1080;

	// O(w*h)
	double m_vertex[1920][1080];
	//計算を考慮する頂点のインターバル
	int m_vertex_interval = 16;

	//インク状態が平衡する時間ms
	int32 m_equilibrium = 1000;
	
	//インクが乾く時間ms
	int32 m_dry_dur = 500;

	//インクが乾くしきい値 (0.0～1.0)
	double m_threshold_dry = 0.10;
	//インクが塗り状態とみなされるしきい値 (0.0～1.0)
	double m_threshold_wet = 0.80;
};

MapSimple* Singleton<MapSimple>::instance = nullptr;