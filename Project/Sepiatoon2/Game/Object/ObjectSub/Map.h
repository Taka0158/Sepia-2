#pragma once

//initializeとenter関数の用途が似すぎ	無駄
class Map :public Object
{
public:
	Map();
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

	bool handle_message(const Telegram&)override;
	bool on_message(const Telegram&)override;

	//引数ピクセル場所の色を返す
	Color get_color(Point);
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
	Texture m_tex_background;

	int m_map_w = 1920;
	int m_map_h = 1080;

	//更新間隔
	int m_update_interval;

	int m_timer;

	//色塗りの行列
	std::queue<Paint> que;
};

