#pragma once

//�Ǘ�����UI�q�N���X���������ObjectManager�̂悤�ȐU�镑���ɕύX���ׂ�
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

	//�e�X�g�N���X
	//�o�ߎ���(�b)��\������N���X
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
			FONT_IKA_ALPHABET_32.drawCenter(ToString(sec), Vec2(sc_w / 2, 64), Palette::Black);
		}
	private:
		int timer;
		int sec;
	};

	UITime* m_UITime = nullptr;
};

UIManager* Singleton<UIManager>::instance = nullptr;