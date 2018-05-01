#pragma once

class SelectChar :public Scene
{
public:
	SelectChar();
	~SelectChar();

	void initialize();
	void finalize();

	void enter();
	void update();
	void draw();
	void debug_update();
	void debug_draw();
	void exit();

	void input()override;


private:
	//決定キーによる準備完了の切り替えを行う
	void toggle_ready();

	//選択中のキャラクタ表示を行う
	void draw_charcter();
	void draw_frame();

	//キャラ選択の決定を行う
	void decide_p1(CharType);
	void decide_p2(CharType);

	//表示中のキャラクタの画像を取ってくる
	Texture* get_tex(CharType);

	//キャラクタの説明を行う
	void chara_describe();

	//説明データの入力
	void get_char_info(std::vector<String>& _container, CharType _type);

	//準備完了からの経過時間
	int m_ready_timer;

	//準備完了からの待ち時間
	static int m_ready_durtion;

	//準備ができたかどうか
	bool m_is_ready_p1;
	bool m_is_ready_p2;
	//表示中のキャラタイプ
	int m_index_p1;
	int m_index_p2;
};

int SelectChar::m_ready_durtion = 90;