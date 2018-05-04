#pragma once

//initializeとenter関数の用途が似すぎ	無駄
class Map :public Object
{
public:
	Map(MapType _type);
	virtual ~Map();
	virtual void initialize() {};
	virtual void finalize() {};
	//Sceneの入った際に呼び出される
	virtual void enter();
	//メイン更新
	virtual void update() ;
	virtual void draw() ;
	//Sceneを出る際に呼び出される
	virtual void exit() ;

	virtual void debug_update();
	virtual void debug_draw();

	//単一オブジェクトよりidはマクロ指定
	virtual void set_id() {};
	void init_id()override {};

	bool handle_message(const Telegram&)override;
	bool on_message(const Telegram&)override;

	//引数ピクセル場所の色を返す
	Color get_color(Point);

	//マップサイズを返す
	Size get_map_size() { return Size(m_map_w, m_map_h); }

	MapType get_map_type() { return m_map_type; }
protected:
	//画像処理（ブレンド）を行う
	void blend();
	//blendの予約を行う
	void paint(Paint _p);
	//背景画像を指定する
	virtual void set_background_im() = 0;
	//工場クラスからランダムにインク画像を得る
	Image& get_random_ink();
	//Imageをランダムに回転させる
	Image& rotate_image(Image&);
protected:
	Image m_im_background;
	DynamicTexture m_tex_background;

	int m_map_w = 1920;
	int m_map_h = 1080;

	//更新間隔
	int m_update_interval=1;

	int m_timer;

	//色塗りの行列
	std::queue<Paint> que;

	//自分のマップタイプ
	MapType m_map_type;
};


#include"MapSub\MapSimple.cpp"
#include"MapSub\MapSimpleBig.cpp"
#include"MapSub\MapClassic.cpp"