#pragma once

//-----------------------------------debug---------------------------------
class DebugText
{
public:
	DebugText(double _time, String _info)
	{
		time = Setting::stopwatch.s() + _time;
		info = _info;
	}
	//表示継続時間
	double time;
	//付加情報
	String info;
};
bool operator==(const DebugText& t1, const DebugText& t2)
{
	return (t1.time - t2.time < 0.0001);
}
bool operator<(const DebugText&t1, const DebugText&t2)
{
	if (t1 == t2)return false;
	else return (t1.time < t2.time);
}
class Debug :public Singleton<Debug>
{
	friend class Singleton<Debug>;
public:
	void update()
	{
		show_mouse_pos();

		//フルスクリーン切り替え
		if (Input::KeyF4.clicked)
		{
			Setting::toggle_fullscreen();
		}

		//fps表示
		Println(Profiler::FPS(), L"FPS");

		if (texts.empty())return;
		check();
			for (auto itr : texts)
		{
			Println(itr.info);
		}
	}
	void regist(DebugText _text)
	{
		texts.push_back(_text);
	}
private:
	//期限切れのデバッグテキストを削除
	void check()
	{
		if (texts.empty())return;

		auto isInvalid = [](DebugText& text)
		{
			return text.time <= Setting::stopwatch.s();
		};

		auto rmvIter = std::remove_if(texts.begin(), texts.end(), isInvalid);

		texts.erase(rmvIter, texts.end());
	}
	//マウスの座標を表示
	void show_mouse_pos()
	{
		Println(L"マウス座標:",Mouse::Pos() );
	}
private:
	static std::vector<DebugText> texts;
};
std::vector<DebugText> Debug::texts = std::vector<DebugText>();
Debug* Singleton<Debug>::instance = nullptr;
//-----------------------------------debug---------------------------------