#pragma once

/*
MediaPlayerは再生中は何も描画できない
VideoPlayerはうまく機能しない…
TODO
*/
class IkaCutin :public CutScene
{
public:
	IkaCutin();
	~IkaCutin();

	void enter(Scene*)override;
	void update_sub(Scene*)override;
	void draw_sub(Scene*)override;
	void exit(Scene*)override;
private:
	//使用する動画のポインタ
	VideoPlayer* m_using_video=nullptr;
	
	//スタート座標　中央からどれだけ離れているか
	int m_start_pos = 300;

	//表示領域
	Rect m_region = Rect(Point(0.0, 0.0), Vec2_to_Point(Setting::get_sc()));
};