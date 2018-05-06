#pragma once

#include"Indicatable.h"

//管理するUI子クラスが増えればObjectManagerのような振る舞いに変更すべき
class UIManager :public Entity, public Singleton<UIManager>
{
	friend class Singleton<UIManager>;
public:
	UIManager();
	~UIManager();

	void update();
	void draw();

	void debug_update();
	void debug_draw();

	void initialize();
	void finalize();

	bool handle_message(const Telegram&);
private:
	bool on_message(const Telegram&);

	//UI表示するオブジェクトの登録
	void register_object(Indicatable*);

	//登録されたオブジェクトの表示
	void draw_indicators();

	//テストクラス
	//経過時間(秒)を表示するクラス
	class UITime
	{
	public:
		UITime()
		{
			timer = 1;
			sec = 0;
		}
		void update()
		{
			timer++;
			if (timer % 60 == 0)sec++;
		}
		void draw()
		{
			int sc_w = Setting::sc_w;
			FONT_IKA_ALPHABET(32).drawCenter(ToString(sec), Vec2(sc_w / 2, 64), Palette::Black);
		}
	private:
		int timer;
		int sec;
	};

	UITime* m_UITime = nullptr;

	//UIを表示するオブジェクト
	//登録することで描画深度に関わらず表示できる
	//削除はfinalize関数でのみ行う
	std::vector<Indicatable*> m_indicators;
};

UIManager* Singleton<UIManager>::instance = nullptr;