#pragma once

/*
MediaPlayerは再生中は何も描画できない
VideoPlayerはうまく機能しない…
TODO
*/
class IkaCutin :public CutScene
{
public:
	IkaCutin(Color _color);
	~IkaCutin();

	void enter(Scene*)override;
	void update_sub(Scene*)override;
	void draw_sub(Scene*)override;
	void exit(Scene*)override;
private:
	
	//スタート座標　中央からどれだけ離れているか
	int m_start_pos = 2000;

	Color m_color;

};