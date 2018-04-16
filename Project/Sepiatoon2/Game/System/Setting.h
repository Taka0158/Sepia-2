#pragma once

class Setting :public Singleton<Setting>
{
	friend class Singleton<Setting>;
private:
	Setting()
	{
		stopwatch.start();

		Graphics::SetBackground(Palette::Gray);
	};
	~Setting() {};
public:
	static void window_resize(int w, int h)
	{
		Window::Resize(w, h);
		sc_w = w;
		sc_h = h;
	};
	static void toggle_fullscreen()
	{
		if (Window::IsFullSceen())
		{
			sc_w = window_sc_w;
			sc_h = window_sc_h;
			Window::SetFullscreen(false, Size(sc_w, sc_h));
		}
		else
		{
			sc_w = full_sc_w;
			sc_h = full_sc_h;
			Window::SetFullscreen(true, Size(sc_w, sc_h));
		}
	
	}
	static Size get_size()
	{
		return Size(sc_w, sc_h);
	};

	static Vec2 get_sc()
	{
		return Vec2(sc_w, sc_h);
	}

	//�X�g�b�v�E�H�b�`
	static Stopwatch stopwatch;

	static int32 get_ms()
	{
		return stopwatch.ms();
	}

	//�𑜓x
	static int sc_w;
	static int sc_h;
	static int full_sc_w;
	static int full_sc_h;
	static int window_sc_w;
	static int window_sc_h;
};
Stopwatch Setting::stopwatch = Stopwatch();
Setting* Setting::instance = nullptr;

int Setting::sc_w = 640;
int Setting::sc_h = 480;

//�E�B���h�E�𑜓x
int Setting::window_sc_w = 640;
int Setting::window_sc_h = 480;

//�t���X�N���[���𑜓x
int Setting::full_sc_w = 1920;
int Setting::full_sc_h = 1080;
